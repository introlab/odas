
   /**
    * \file     freq2acorr.c
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
