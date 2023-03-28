
   /**
    * \file     freq2env.c
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
   
    #include <system/freq2env.h>

    freq2env_obj * freq2env_construct_zero(const unsigned int halfFrameSize) {

        freq2env_obj * obj;

        obj = (freq2env_obj *) malloc(sizeof(freq2env_obj));

        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void freq2env_destroy(freq2env_obj * obj) {

        free((void *) obj);

    }

    void freq2env_process(freq2env_obj * obj, const freqs_obj * freqs, envs_obj * envs) {

        unsigned int iSignal;
        unsigned int iBin;

        float Xreal;
        float Ximag;
        float X2;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                Xreal = freqs->array[iSignal][iBin * 2 + 0];
                Ximag = freqs->array[iSignal][iBin * 2 + 1];

                X2 = Xreal * Xreal + Ximag * Ximag;

                envs->array[iSignal][iBin] = X2;

            }

        }

    }
