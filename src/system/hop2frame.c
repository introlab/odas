
   /**
    * \file     hop2frame.c
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
    
    #include <system/hop2frame.h>

    hop2frame_obj * hop2frame_construct_zero(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nSignals) {

        hop2frame_obj * obj;
        unsigned int iSignal;

        obj = (hop2frame_obj *) malloc(sizeof(hop2frame_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;
        obj->nSignals = nSignals;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * frameSize);
            memset(obj->array[iSignal], 0x00, sizeof(float) * frameSize);
        }

        return obj;

    }

    void hop2frame_destroy(hop2frame_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void hop2frame_process(hop2frame_obj * obj, const hops_obj * hops, frames_obj * frames) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < hops->nSignals; iSignal++) {

            memmove(&(obj->array[iSignal][0]),
                    &(obj->array[iSignal][obj->hopSize]),
                    sizeof(float) * (obj->frameSize-obj->hopSize));

            memcpy(&(obj->array[iSignal][(obj->frameSize-obj->hopSize)]),
                   &(hops->array[iSignal][0]),
                   sizeof(float) * obj->hopSize);

            memcpy(frames->array[iSignal],
                   obj->array[iSignal],
                   sizeof(float) * obj->frameSize);

        }        

    }
