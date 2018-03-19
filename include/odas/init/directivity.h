#ifndef __ODAS_INIT_DIRECTIVITY
#define __ODAS_INIT_DIRECTIVITY

   /**
    * \file     directivity.h
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

    #include <stdlib.h>
    #include <math.h>

    #include <general/mic.h>
    #include <general/spatialfilter.h>

    #include <signal/beampattern.h>
    #include <signal/pair.h>
    #include <signal/point.h>
    #include <signal/spatialgain.h>
    #include <signal/spatialindex.h>
    #include <signal/spatialmask.h>

    beampatterns_obj * directivity_beampattern_mics(const mics_obj * mics, const unsigned int nThetas);

    beampatterns_obj * directivity_beampattern_spatialfilter(const spatialfilter_obj * spatialfilter, const unsigned int nThetas);

    spatialgains_obj * directivity_spatialgains(const mics_obj * mics, const beampatterns_obj * beampatterns_mics, const spatialfilter_obj * spatialfilter, const beampatterns_obj * beampatterns_spatialfilter, const points_obj * points);

    spatialmasks_obj * directivity_spatialmasks(const spatialgains_obj * spatialgains, const float minGain);

    spatialindexes_obj * directivity_spatialindexes(const spatialmasks_obj * spatialmasks);

    pairs_obj * directivity_pairs(const spatialmasks_obj * spatialmasks);

    void directivity_pairsadd(pairs_obj * destPairs, const pairs_obj * srcPairs);

#endif
