   
   /**
    * \file     index.c
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
    
    #include <signal/index.h>

    indexes_obj * indexes_construct_zero(const unsigned int nCoarses, const unsigned int nFines) {

        indexes_obj * obj;

        obj = (indexes_obj *) malloc(sizeof(indexes_obj));

        obj->nCoarses = nCoarses;
        obj->nFines = nFines;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nCoarses * nFines);
        memset(obj->array, 0x00, sizeof(unsigned int) * nCoarses * nFines);
        obj->count = (unsigned int *) malloc(sizeof(unsigned int) * nCoarses);
        memset(obj->count, 0x00, sizeof(unsigned int) * nCoarses);

        return obj;

    }

    void indexes_destroy(indexes_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->count);
        free((void *) obj);

    }

    void indexes_printf(const indexes_obj * obj) {

        unsigned int iCoarse;
        unsigned int iFine;

        for (iCoarse = 0; iCoarse < obj->nCoarses; iCoarse++) {

            printf("(%04u): ",iCoarse);

            if (obj->count[iCoarse] > 0) {

                for (iFine = 0; iFine < obj->count[iCoarse]; iFine++) {

                    printf("%04u ",obj->array[iCoarse * obj->nFines + iFine]);

                }

            }
            else {

                printf("-");

            }

            printf("\n");

        }

    }
