
   /**
    * \file     freq2acorr.c
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
    
    #include <system/freq2acorr.h>

    freq2acorr_obj * freq2acorr_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        freq2acorr_obj * obj;

        obj = (freq2acorr_obj *) malloc(sizeof(freq2acorr_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        obj->frameSize = (halfFrameSize-1)*2;

        obj->arrayIn = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
        obj->arrayOut = (float *) malloc(sizeof(float) * obj->frameSize);

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void freq2acorr_destroy(freq2acorr_obj * obj) {

        free((void *) obj->arrayIn);
        free((void *) obj->arrayOut);
        fft_destroy(obj->fft);
        free((void *) obj);

    }

    void freq2acorr_process(freq2acorr_obj * obj, const freqs_obj * freqs, acorrs_obj * acorrs) {

        unsigned int iSignal;
        unsigned int iBin;

        float Yreal;
        float Yimag;
        float Ypwr;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            memset(obj->arrayIn, 0x00, sizeof(float) * obj->halfFrameSize * 2);

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                Yreal = freqs->array[iSignal][iBin * 2 + 0];
                Yimag = freqs->array[iSignal][iBin * 2 + 1];
                Ypwr = Yreal * Yreal + Yimag * Yimag;

                obj->arrayIn[iBin * 2 + 0] = Ypwr;
                obj->arrayIn[iBin * 2 + 1] = 0.0f;

            }

            fft_c2r(obj->fft, obj->arrayIn, obj->arrayOut);

            memcpy(acorrs->array[iSignal], obj->arrayOut, sizeof(float) * obj->halfFrameSize);

        }

    }
