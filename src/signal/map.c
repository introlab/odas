   
   /**
    * \file     map.c
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

    #include <signal/map.h>

    maps_obj * maps_construct_zero(const unsigned int nCoarses, const unsigned int nFines) {

        maps_obj * obj;

        obj = (maps_obj *) malloc(sizeof(maps_obj));

        obj->nCoarses = nCoarses;
        obj->nFines = nFines;
        
        obj->array = (char *) malloc(sizeof(char) * nFines * nCoarses);
        memset(obj->array, 0x00, sizeof(char) * nFines * nCoarses);

        return obj;

    }

    void maps_destroy(maps_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void maps_printf(const maps_obj * obj) {

        unsigned int iFine;
        unsigned int iCoarse;

        for (iFine = 0; iFine < obj->nFines; iFine++) {

            printf("(%04u): ",iFine);

            for (iCoarse = 0; iCoarse < obj->nCoarses; iCoarse++) {

                printf("%01u",obj->array[iFine * obj->nCoarses + iCoarse]);

            }

            printf("\n");

        }

    }
