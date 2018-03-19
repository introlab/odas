   
   /**
    * \file     spatialmask.c
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
    
    #include <signal/spatialmask.h>

    spatialmasks_obj * spatialmasks_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        spatialmasks_obj * obj;

        obj = (spatialmasks_obj *) malloc(sizeof(spatialmasks_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->array = (char *) malloc(sizeof(char) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(char) * nPoints * nPairs);

        return obj;

    }

    spatialmasks_obj * spatialmasks_clone(const spatialmasks_obj * obj) {

        spatialmasks_obj * clone;

        clone = (spatialmasks_obj *) malloc(sizeof(spatialmasks_obj));

        clone->nPoints = obj->nPoints;
        clone->nPairs = obj->nPairs;

        clone->array = (char *) malloc(sizeof(char) * obj->nPoints * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(char) * obj->nPoints * obj->nPairs);

        return clone;

    }

    void spatialmasks_destroy(spatialmasks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void spatialmasks_printf(const spatialmasks_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                if (obj->array[iPoint * obj->nPairs + iPair] != 0x00) {

                    printf("1");

                }
                else {

                    printf("0");

                }

            }

            printf("\n");            

        }

    }
