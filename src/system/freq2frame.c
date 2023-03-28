
   /**
    * \file     freq2frame.c
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
    
    #include <system/freq2frame.h>

    freq2frame_obj * freq2frame_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        freq2frame_obj * obj;

        obj = (freq2frame_obj *) malloc(sizeof(freq2frame_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->win = windowing_roothann(frameSize);
        obj->frame = (float *) malloc(sizeof(float) * frameSize);
        memset(obj->frame, 0x00, sizeof(float) * frameSize);
        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void freq2frame_destroy(freq2frame_obj * obj) {

        window_destroy(obj->win);
        free((void *) obj->frame);
        fft_destroy(obj->fft);

        free((void *) obj);        

    }

    void freq2frame_process(freq2frame_obj * obj, const freqs_obj * freqs, frames_obj * frames) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < frames->nSignals; iSignal++) {

            fft_c2r(obj->fft, 
                    freqs->array[iSignal],
                    obj->frame);

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                frames->array[iSignal][iSample] = obj->win->array[iSample] * obj->frame[iSample];

            }

        }

    }
