  
   /**
    * \file     hop.c
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
    
    #include <signal/hop.h>

    hops_obj * hops_construct_zero(const unsigned int nSignals, const unsigned int hopSize) {

        hops_obj * obj;
        unsigned int iSignal;

        obj = (hops_obj *) malloc(sizeof(hops_obj));

        obj->nSignals = nSignals;
        obj->hopSize = hopSize;
        
        obj->array = (float **) malloc(sizeof(float *) * nSignals);
        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * hopSize);
            memset(obj->array[iSignal], 0x00, hopSize * sizeof(float));
        }

        return obj;

    }

    hops_obj * hops_clone(const hops_obj * obj) {

        hops_obj * clone;
        unsigned int iSignal;

        clone = (hops_obj *) malloc(sizeof(hops_obj));

        clone->nSignals = obj->nSignals;
        clone->hopSize = obj->hopSize;

        clone->array = (float **) malloc(sizeof(float *) * obj->nSignals);
        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            clone->array[iSignal] = (float *) malloc(sizeof(float) * obj->hopSize);
            memcpy(clone->array[iSignal], obj->array[iSignal], obj->hopSize * sizeof(float));
        }

        return clone;

    }

    void hops_copy(hops_obj * dest, const hops_obj * src) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {
            memcpy(dest->array[iSignal], src->array[iSignal], src->hopSize * sizeof(float));
        }

    }

    void hops_zero(hops_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            memset(obj->array[iSignal], 0x00, obj->hopSize * sizeof(float));
        }        

    }

    void hops_destroy(hops_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);    
        }
        free((void *) obj->array);
        
        free((void *) obj);

    }

    void hops_printf(const hops_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal][iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->hopSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }
