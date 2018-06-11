
   /**
    * \file     scanning.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <init/scanning.h>

    scans_obj * scanning_init_scans(const mics_obj * mics, const spatialfilters_obj * spatialfilters, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const unsigned int nMatches, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels, const unsigned int nThetas, const float gainMin, const unsigned int interpRate) {

        scans_obj * obj;
        unsigned int iLevel;

        beampatterns_obj * beampatterns_mics;
        beampatterns_obj * beampatterns_spatialfilters;
        spatialgains_obj * spatialgains;
        spatialmasks_obj ** spatialmasks;
        pairs_obj * pairs;        
        points_obj * pointsRefined;   
        taus_obj * taus;   
        maps_obj * maps;     

        obj = scans_construct_null(nLevels);       

        obj->pairs = pairs_construct_zero(mics->nPairs);
        beampatterns_mics = directivity_beampattern_mics(mics, nThetas);      
        beampatterns_spatialfilters = directivity_beampattern_spatialfilters(spatialfilters, nThetas);

        spatialmasks = (spatialmasks_obj **) malloc(sizeof(spatialmasks_obj *) * nLevels);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            // Generate points
            obj->points[iLevel] = space_sphere(levels[iLevel]);

            // Generate TDOAs
            obj->tdoas[iLevel] = delay_tdoas(obj->points[iLevel], 
                                             mics, 
                                             soundspeed, 
                                             fS, 
                                             frameSize,
                                             interpRate);            

            // Generate gains in space
            spatialgains = directivity_spatialgains(mics, 
                                                    beampatterns_mics,
                                                    spatialfilters, 
                                                    beampatterns_spatialfilters,
                                                    obj->points[iLevel]);           

            // Generate masks in space
            spatialmasks[iLevel] = directivity_spatialmasks(spatialgains, 
                                                            gainMin);    
            spatialgains_destroy(spatialgains);

            // Generate masks for pairs
            pairs = directivity_pairs(spatialmasks[iLevel]);
            directivity_pairsadd(obj->pairs, pairs);
            pairs_destroy(pairs);

            // Generate indexes in space
            obj->spatialindexes[iLevel] = directivity_spatialindexes(spatialmasks[iLevel]);

            // Generate deltas
            if (deltas[iLevel] < 0) {

                pointsRefined = space_points_fine(obj->points[iLevel],
                                                  nRefineLevels);

                taus = delay_taus(pointsRefined, 
                                  mics, 
                                  soundspeed, 
                                  fS, 
                                  frameSize,
                                  interpRate);

                obj->deltas[iLevel] = hit_train(taus, 
                                                obj->tdoas[iLevel], 
                                                spatialmasks[iLevel], 
                                                probMin);

                points_destroy(pointsRefined);

                taus_destroy(taus);

            }
            else {

                obj->deltas[iLevel] = hit_constant(obj->tdoas[iLevel], 
                                                   deltas[iLevel]);

            }

        }

        beampatterns_destroy(beampatterns_mics);
        beampatterns_destroy(beampatterns_spatialfilters);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            if (iLevel == 0) {

                maps = linking_maps(NULL, obj->tdoas[0], 
                                    NULL, obj->deltas[0], 
                                    NULL, spatialmasks[0], 
                                    nMatches);       

            }
            else {

                maps = linking_maps(obj->tdoas[iLevel-1], obj->tdoas[iLevel], 
                                    obj->deltas[iLevel-1], obj->deltas[iLevel], 
                                    spatialmasks[iLevel-1], spatialmasks[iLevel],
                                    nMatches);          

            }

            obj->indexes[iLevel] = linking_indexes(maps);

            maps_destroy(maps);

        }

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            spatialmasks_destroy(spatialmasks[iLevel]);

        }

        free((void *) spatialmasks);

        return obj;

    }
