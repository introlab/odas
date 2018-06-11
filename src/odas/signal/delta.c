
   /**
    * \file     delta.c
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

    #include <signal/delta.h>

    deltas_obj * deltas_construct_zero(const unsigned int nPairs) {

        deltas_obj * obj;

        obj = (deltas_obj *) malloc(sizeof(deltas_obj));

        obj->nPairs = nPairs;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPairs);

        return obj;

    }

    deltas_obj * deltas_clone(const deltas_obj * obj) {

        deltas_obj * clone;

        clone = (deltas_obj *) malloc(sizeof(deltas_obj));

        clone->nPairs = obj->nPairs;
        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nPairs);

        return clone;

    }

    void deltas_destroy(deltas_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void deltas_printf(const deltas_obj * obj) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("(%02u): %02u\n",iPair,obj->array[iPair]);

        }

    }
