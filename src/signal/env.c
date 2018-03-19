
   /**
    * \file     env.c
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
    
    #include <signal/env.h>

    envs_obj * envs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        envs_obj * obj;
        unsigned int iSignal;

        obj = (envs_obj *) malloc(sizeof(envs_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        
        obj->array = (float **) malloc(sizeof(float *) * nSignals);
        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->array[iSignal], 0x00, halfFrameSize * sizeof(float));
        }

        return obj;

    }

    envs_obj * envs_clone(const envs_obj * obj) {

        envs_obj * clone;
        unsigned int iSignal;

        clone = (envs_obj *) malloc(sizeof(envs_obj));

        clone->nSignals = obj->nSignals;
        clone->halfFrameSize = obj->halfFrameSize;

        clone->array = (float **) malloc(sizeof(float *) * obj->nSignals);
        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            clone->array[iSignal] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memcpy(clone->array[iSignal], obj->array[iSignal], obj->halfFrameSize * sizeof(float));
        }

        return clone;

    }

    void envs_copy(envs_obj * dest, const envs_obj * src) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {
            memcpy(dest->array[iSignal], src->array[iSignal], src->halfFrameSize * sizeof(float));
        }

    }

    void envs_zero(envs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            memset(obj->array[iSignal], 0x00, obj->halfFrameSize * sizeof(float));
        }

    }

    void envs_destroy(envs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }
        free((void *) obj->array);

        free((void *) obj);

    }

    void envs_printf(const envs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                printf("%+1.5f ",
                       obj->array[iSignal][iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->halfFrameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }        

    }
