   
   /**
    * \file     xcorr.c
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
    
    #include <signal/xcorr.h>

    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        xcorrs_obj * obj;
        unsigned int iSignal;

        obj = (xcorrs_obj *) malloc(sizeof(xcorrs_obj));

        obj->nSignals = nSignals;
        obj->frameSize = frameSize;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);
        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * frameSize);
            memset(obj->array[iSignal], 0x00, frameSize * sizeof(float));    
        }
        
        return obj;

    }

    void xcorrs_destroy(xcorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }
        free((void *) obj->array);

        free((void *) obj);

    }

    void xcorrs_copy(xcorrs_obj * dest, const xcorrs_obj * src) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {
            memcpy(dest->array[iSignal], src->array[iSignal], src->frameSize * sizeof(float));
        }

    }

    void xcorrs_zero(xcorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            memset(obj->array[iSignal], 0x00, obj->frameSize * sizeof(float));
        }

    }

    void xcorrs_printf(const xcorrs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal][iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->frameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }

    void xcorrs_printf_signal(const xcorrs_obj * obj, const unsigned int iSignal) {

        unsigned int iSample;

        printf("(%04u): ",iSignal);

        for (iSample = 0; iSample < obj->frameSize; iSample++) {

            printf("%+1.5f ",obj->array[iSignal][iSample]);

            if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->frameSize)) {
                printf("\n        ");
            }

        }

        printf("\n");

    }
