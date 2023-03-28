
   /**
    * \file     coherence.c
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

    #include <signal/coherence.h>

    coherences_obj * coherences_construct_zero(const unsigned int nPots, const unsigned int nTracks) {

        coherences_obj * obj;
        obj = (coherences_obj *) malloc(sizeof(coherences_obj));
        obj->nPots = nPots;
        obj->nTracks = nTracks;
        obj->array = (float *) malloc(sizeof(float) * nTracks * nPots);
        memset(obj->array, 0x00, sizeof(float) * nTracks * nPots);

        return obj;

    }

    void coherences_destroy(coherences_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void coherences_printf(coherences_obj * obj) {

        unsigned int iTrack;
        unsigned int iPot;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("p(z|C,%u) = ",iTrack);

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+1.3e ",obj->array[iTrack * obj->nPots + iPot]);

            }

            printf("\n");

        }

    }
