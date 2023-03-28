
   /**
    * \file     frame2hop.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */
    
    #include <system/frame2hop.h>
    
    frame2hop_obj * frame2hop_construct_zero(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nSignals) {

        frame2hop_obj * obj;
        unsigned int iSignal;

        obj = (frame2hop_obj *) malloc(sizeof(frame2hop_obj));

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

    void frame2hop_destroy(frame2hop_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }

        free((void *) obj->array);

        free((void *) obj);

    }

    void frame2hop_process(frame2hop_obj * obj, const frames_obj * frames, hops_obj * hops) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            memmove(&(obj->array[iSignal][0]),
                    &(obj->array[iSignal][obj->hopSize]),
                    sizeof(float) * (obj->frameSize - obj->hopSize));

            memset(&(obj->array[iSignal][obj->frameSize - obj->hopSize]),
                   0x00,
                   sizeof(float) * (obj->hopSize));

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                obj->array[iSignal][iSample] += frames->array[iSignal][iSample];

            }

            memcpy(&(hops->array[iSignal][0]),
                   &(obj->array[iSignal][0]),
                   sizeof(float) * obj->hopSize);

        }

    }
