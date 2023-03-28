
   /**
    * \file     freq2xcorr.c
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
    
    #include <system/freq2xcorr.h>

    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        freq2xcorr_obj * obj;

        obj = (freq2xcorr_obj *) malloc(sizeof(freq2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->frame = (float *) malloc(sizeof(float) * halfFrameSize * 2);
        memset(obj->frame,0x00,sizeof(float)* halfFrameSize * 2);

        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void freq2xcorr_destroy(freq2xcorr_obj * obj) {

        fft_destroy(obj->fft);
        free((void *) obj->frame);

        free((void *) obj);

    }

        void freq2xcorr_process(freq2xcorr_obj * obj, const freqs_obj * freqs, const pairs_obj * pairs, xcorrs_obj * xcorrs) {

        unsigned int iSignal;
        unsigned int iSample;
        unsigned int iSampleSrc;
        unsigned int iSampleDest;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            if (pairs->array[iSignal] == 0x01) {

                fft_c2r(obj->fft, 
                        freqs->array[iSignal],
                        obj->frame);

                memcpy(&(xcorrs->array[iSignal][0]),&(obj->frame[obj->frameSize/2]),(obj->frameSize/2)*sizeof(float));
                memcpy(&(xcorrs->array[iSignal][obj->frameSize/2]),&(obj->frame[0]),(obj->frameSize/2)*sizeof(float));

            }

        }

    }
