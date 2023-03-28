
   /**
    * \file     scanning.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
