#ifndef __ODAS_INIT_LINKING
#define __ODAS_INIT_LINKING

   /**
    * \file     linking.h
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

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>

    #include <signal/delta.h>
    #include <signal/index.h>
    #include <signal/map.h>
    #include <signal/tdoa.h>
    #include <signal/spatialmask.h>

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const deltas_obj * deltasCoarse, const deltas_obj * deltasFine, const spatialmasks_obj * spatialmasksCoarse, const spatialmasks_obj * spatialmasksFine, const unsigned int nMatches);

    indexes_obj * linking_indexes(const maps_obj * maps);

    float linking_overlap(const float lambdaCoarseLeft, const float lambdaCoarseRight, const float lambdaFineLeft, const float lambdaFineRight);

#endif
