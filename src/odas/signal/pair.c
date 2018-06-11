   
   /**
    * \file     pair.c
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

    #include <signal/pair.h>

    pairs_obj * pairs_construct_zero(const unsigned int nPairs) {

        pairs_obj * obj;

        obj = (pairs_obj *) malloc(sizeof(pairs_obj));

        obj->nPairs = nPairs;
        obj->array = (char *) malloc(sizeof(char) * nPairs);
        memset(obj->array, 0x00, sizeof(char) * nPairs);

        return obj;

    }

    pairs_obj * pairs_clone(const pairs_obj * obj) {

        pairs_obj * clone;

        clone = (pairs_obj *) malloc(sizeof(pairs_obj));

        clone->nPairs = obj->nPairs;
        clone->array = (char *) malloc(sizeof(char) * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(char) * obj->nPairs);        

        return clone;

    }

    void pairs_destroy(pairs_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pairs_printf(const pairs_obj * obj) {

        unsigned int iPair;

        printf("nPairs: %u\n", obj->nPairs);
        
        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            printf("(%02u): %d\n", iPair, obj->array[iPair]);    
        }

    }
