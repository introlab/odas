
   /**
    * \file     freq.c
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
    
    #include <signal/freq.h>

    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        freqs_obj * obj;
        unsigned int iSignal;

        obj = (freqs_obj *) malloc(sizeof(freqs_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        
        obj->array = (float **) malloc(sizeof(float *) * nSignals);
        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * halfFrameSize * 2);
            memset(obj->array[iSignal], 0x00, halfFrameSize * 2 * sizeof(float));
        }

        return obj;

    }

    freqs_obj * freqs_clone(const freqs_obj * obj) {

        freqs_obj * clone;
        unsigned int iSignal;

        clone = (freqs_obj *) malloc(sizeof(freqs_obj));

        clone->nSignals = obj->nSignals;
        clone->halfFrameSize = obj->halfFrameSize;

        clone->array = (float **) malloc(sizeof(float *) * obj->nSignals);
        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            clone->array[iSignal] = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
            memcpy(clone->array[iSignal], obj->array[iSignal], obj->halfFrameSize * 2 * sizeof(float));
        }

        return clone;

    }

    void freqs_copy(freqs_obj * dest, const freqs_obj * src) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {
            memcpy(dest->array[iSignal], src->array[iSignal], src->halfFrameSize * 2 * sizeof(float));
        }

    }

    void freqs_zero(freqs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            memset(obj->array[iSignal], 0x00, obj->halfFrameSize * 2 * sizeof(float));
        }

    }

    void freqs_destroy(freqs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }
    	free((void *) obj->array);

    	free((void *) obj);

    }

    void freqs_printf(const freqs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                printf("(%+1.5f + %+1.5fj) ",
                       obj->array[iSignal][iSample*2 + 0],
                       obj->array[iSignal][iSample*2 + 1]);

                if ((((iSample+1) % 8) == 0) && ((iSample+1)!=obj->halfFrameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }        

    }
