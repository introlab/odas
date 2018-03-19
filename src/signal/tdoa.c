   
   /**
    * \file     tdoa.c
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
    
    #include <signal/tdoa.h>

    tdoas_obj * tdoas_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        tdoas_obj * obj;

        obj = (tdoas_obj *) malloc(sizeof(tdoas_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPoints * nPairs);

        obj->min = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->min, 0x00, sizeof(unsigned int) * nPairs);

        obj->max = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->max, 0x00, sizeof(unsigned int) * nPairs);

        return obj;

    }

    void tdoas_destroy(tdoas_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->min);
        free((void *) obj->max);
        free((void *) obj);

    }

    void tdoas_printf(const tdoas_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                printf("%04u ",obj->array[iPoint * obj->nPairs + iPair]);

            }

            printf("\n");

        }

        printf("(min): ");

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("%04u ",obj->min[iPair]);

        }

        printf("\n");

        printf("(max): ");

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("%04u ",obj->max[iPair]);

        }

        printf("\n");

    }
