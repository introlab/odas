   
   /**
    * \file     spatialindex.c
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

    #include <signal/spatialindex.h>

    spatialindexes_obj * spatialindexes_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        spatialindexes_obj * obj;

        obj = (spatialindexes_obj *) malloc(sizeof(spatialindexes_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;
        
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPoints * nPairs);

        obj->count = (unsigned int *) malloc(sizeof(unsigned int) * nPoints);
        memset(obj->count, 0x00, sizeof(unsigned int) * nPoints);

        return obj;

    }

    spatialindexes_obj * spatialindexes_clone(const spatialindexes_obj * obj) {

        spatialindexes_obj * clone;

        clone = (spatialindexes_obj *) malloc(sizeof(spatialindexes_obj));

        clone->nPoints = obj->nPoints;
        clone->nPairs = obj->nPairs;

        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPoints * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nPoints * obj->nPairs);

        clone->count = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPoints);
        memcpy(clone->count, obj->count, sizeof(unsigned int) * obj->nPoints);

        return clone;

    }

    void spatialindexes_destroy(spatialindexes_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->count);

        free((void *) obj);

    }

    void spatialindexes_printf(const spatialindexes_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            if (obj->count[iPoint] > 0) {

                for (iPair = 0; iPair < obj->count[iPoint]; iPair++) {

                    printf("%03u ",obj->array[iPoint * obj->nPairs + iPair]);

                }

            }
            else {

                printf("-");

            }

            printf("\n");

        }

    }
