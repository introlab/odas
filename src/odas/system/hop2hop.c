
   /**
    * \file     hop2hop.c
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
    
    #include <system/hop2hop.h>

    hop2hop_multiplex_obj * hop2hop_multiplex_construct_zero(const unsigned int hopSize) {

        hop2hop_multiplex_obj * obj;

        obj = (hop2hop_multiplex_obj *) malloc(sizeof(hop2hop_multiplex_obj));

        obj->hopSize = hopSize;

        return obj;

    }

    void hop2hop_multiplex_destroy(hop2hop_multiplex_obj * obj) {

        free((void *) obj);

    }

    void hop2hop_multiplex_process(hop2hop_multiplex_obj * obj, const links_obj * links, const hops_obj * src, hops_obj * dest) {

        unsigned int iLink;

        for (iLink = 0; iLink < links->nLinks; iLink++) {

            if (links->array[iLink] == 0) {

                memset(dest->array[iLink], 0x00, sizeof(float) * obj->hopSize);

            }
            else {

                memcpy(dest->array[iLink], src->array[links->array[iLink]-1], sizeof(float) * obj->hopSize);

            }

        }

    }

    hop2hop_buffer_obj * hop2hop_buffer_construct_zero(const unsigned int nSignals, const unsigned int hopSizeIn, const unsigned int hopSizeOut, const float ratio) {

        hop2hop_buffer_obj * obj;
        unsigned int iSignal;

        obj = (hop2hop_buffer_obj *) malloc(sizeof(hop2hop_buffer_obj));

        obj->nSignals = nSignals;
        obj->hopSizeIn = hopSizeIn;
        obj->hopSizeOut = hopSizeOut;
        obj->intervalIn = (float) hopSizeIn;
        obj->intervalOut = ((float) hopSizeOut) / ratio;
        obj->intervalSize = 0.0f;
        obj->ratio = ratio;
        obj->delta = 1.0f / ratio;

        if (obj->intervalIn >= obj->intervalOut) {

            obj->bufferSize = (unsigned int) ceilf(2.0f * obj->intervalIn);

        }
        else {

            obj->bufferSize = (unsigned int) ceilf(2.0f * obj->intervalOut);

        }

        obj->iRead = 0.0f;
        obj->iWrite = 0.0f;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            
            obj->array[iSignal] = (float *) malloc(sizeof(float) * obj->bufferSize);
            memset(obj->array[iSignal], 0x00, sizeof(float) * obj->bufferSize);

        }

        return obj;

    }

    void hop2hop_buffer_destroy(hop2hop_buffer_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void hop2hop_buffer_push(hop2hop_buffer_obj * obj, const hops_obj * hops) {

        unsigned int iWriteInt;

        unsigned int iHop1;
        unsigned int iBuffer1;
        unsigned int nSamples1;
        unsigned int iHop2;
        unsigned int iBuffer2;
        unsigned int nSamples2;

        unsigned int iSignal;

        if ((obj->intervalSize + obj->intervalIn) <= ((float) obj->bufferSize)) {

            iWriteInt = (unsigned int) obj->iWrite;

            if ((obj->iWrite + obj->intervalIn) <= ((float) obj->bufferSize)) {

                iHop1 = 0;
                iBuffer1 = iWriteInt;
                nSamples1 = (unsigned int) obj->intervalIn;

                iHop2 = 0;
                iBuffer2 = 0;
                nSamples2 = 0;

            }
            else {

                iHop1 = 0;
                iBuffer1 = iWriteInt;
                nSamples1 = (obj->bufferSize - iWriteInt);

                iHop2 = (obj->bufferSize - iWriteInt);
                iBuffer2 = 0;
                nSamples2 = obj->intervalIn - (obj->bufferSize - iWriteInt);

            }

            for (iSignal = 0; iSignal < hops->nSignals; iSignal++) {

                memcpy(&(obj->array[iSignal][iBuffer1]),
                       &(hops->array[iSignal][iHop1]),
                       nSamples1 * sizeof(float));

                memcpy(&(obj->array[iSignal][iBuffer2]),
                       &(hops->array[iSignal][iHop2]),
                       nSamples2 * sizeof(float));

            }

            obj->intervalSize += (float) obj->intervalIn;

            obj->iWrite += (float) obj->intervalIn;
            obj->iWrite = fmod(obj->iWrite, (float) obj->bufferSize);

        }

    }

    void hop2hop_buffer_pop(hop2hop_buffer_obj * obj, hops_obj * hops) {

        unsigned int iSample;
        unsigned int iReadFloor;
        unsigned int iReadCeil;
        float yFloor;
        float yCeil;
        float yDelta;
        float xDelta;

        unsigned int iSignal;

        if (obj->intervalOut <= obj->intervalSize) {

            for (iSample = 0; iSample < obj->hopSizeOut; iSample++) {

                iReadFloor = (unsigned int) floorf(obj->iRead);
                iReadCeil = (iReadFloor + 1) % obj->bufferSize;

                xDelta = obj->iRead - floorf(obj->iRead);
                
                for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

                    yFloor = obj->array[iSignal][iReadFloor];
                    yCeil = obj->array[iSignal][iReadCeil];
                    yDelta = yCeil - yFloor;

                    hops->array[iSignal][iSample] = xDelta * yDelta + yFloor;

                }

                obj->iRead += obj->delta;
                obj->iRead = fmod(obj->iRead, (float) obj->bufferSize);

            }

            obj->intervalSize -= (float) obj->intervalOut;

        }

    }

    char hop2hop_buffer_isFull(hop2hop_buffer_obj * obj) {

        char rtnValue;

        rtnValue = 0;

        if ((obj->intervalSize + obj->intervalIn) > ((float) obj->bufferSize)) {
            
            rtnValue = 1;

        }

        return rtnValue;

    }

    char hop2hop_buffer_isEmpty(hop2hop_buffer_obj * obj) {

        char rtnValue;

        rtnValue = 0;

        if (obj->intervalOut > obj->intervalSize) {
            
            rtnValue = 1;

        }

        return rtnValue;

    }

    hop2hop_gain_obj * hop2hop_gain_construct_zero(const unsigned int hopSize, const float gain) {

        hop2hop_gain_obj * obj;

        obj = (hop2hop_gain_obj *) malloc(sizeof(hop2hop_gain_obj));

        obj->hopSize = hopSize;
        obj->gain = gain;

        return obj;

    }

    void hop2hop_gain_destroy(hop2hop_gain_obj * obj) {

        free((void *) obj);

    }

    void hop2hop_gain_process(hop2hop_gain_obj * obj, const hops_obj * src, hops_obj * dest) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {

            for (iSample = 0; iSample < src->hopSize; iSample++) {

                dest->array[iSignal][iSample] = obj->gain * src->array[iSignal][iSample];

            }

        }

    }
