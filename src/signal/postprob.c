   
   /**
    * \file     postprob.c
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

    #include <signal/postprob.h>

    postprobs_obj * postprobs_construct_zero(const unsigned int nPots, const unsigned int nTracks) {

        postprobs_obj * obj;

        obj = (postprobs_obj *) malloc(sizeof(postprobs_obj));

        obj->nPots = nPots;
        obj->nTracks = nTracks;

        obj->arrayNew = (float *) malloc(sizeof(float) * nPots);
        memset(obj->arrayNew, 0x00, sizeof(float) * nPots);

        obj->arrayTrack = (float *) malloc(sizeof(float) * nTracks * nPots);
        memset(obj->arrayTrack, 0x00, sizeof(float) * nTracks * nPots);

        obj->arrayTrackTotal = (float *) malloc(sizeof(float) * nTracks);
        memset(obj->arrayTrackTotal, 0x00, sizeof(float) * nTracks);        
        
        return obj;

    }    

    void postprobs_destroy(postprobs_obj * obj) {

        free((void *) obj->arrayNew);
        free((void *) obj->arrayTrack);
        free((void *) obj->arrayTrackTotal);
        free((void *) obj);

    }

    void postprobs_printf(const postprobs_obj * obj) {

        unsigned int iTrack;
        unsigned int iPot;

        printf("p(new|E,z): ");

        for (iPot = 0; iPot < obj->nPots; iPot++) {
        
            printf("%+1.3e ",obj->arrayNew[iPot]);

        }

        printf("\n");

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("  p(%u|E,z): ",iTrack);

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+1.3e ",obj->arrayTrack[iTrack * obj->nPots + iPot]);

            }

            printf("> %+1.3f\n",obj->arrayTrackTotal[iTrack]);

        }

    }
