
   /**
    * \file     frame2freq.c
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

    #include <system/frame2freq.h>

    frame2freq_obj * frame2freq_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        frame2freq_obj * obj;

        obj = (frame2freq_obj *) malloc(sizeof(frame2freq_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->win = windowing_roothann(frameSize);
        obj->frame = (float *) malloc(sizeof(float) * frameSize);
        memset(obj->frame, 0x00, sizeof(float) * frameSize);
        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void frame2freq_destroy(frame2freq_obj * obj) {

        window_destroy(obj->win);
        free((void *) obj->frame);
        fft_destroy(obj->fft);

        free((void *) obj);

    }

    void frame2freq_process(frame2freq_obj * obj, const frames_obj * frames, freqs_obj * freqs) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < frames->nSignals; iSignal++) {

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                obj->frame[iSample] = obj->win->array[iSample] * frames->array[iSignal][iSample];

            }

            fft_r2c(obj->fft, 
                    obj->frame,
                    freqs->array[iSignal]);

        }

    }
