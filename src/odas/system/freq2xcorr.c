
   /**
    * \file     freq2xcorr.c
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
