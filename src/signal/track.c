   
   /**
    * \file     track.c
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
    
    #include <signal/track.h>

    tracks_obj * tracks_construct_zero(const unsigned int nTracks) {

        tracks_obj * obj;
        unsigned int iTrack;

        obj = (tracks_obj *) malloc(sizeof(tracks_obj));

        obj->nTracks = nTracks;
        obj->array = (float *) malloc(sizeof(float) * 3 * nTracks);
        memset(obj->array, 0x00, sizeof(float) * 3 * nTracks);
        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * nTracks);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * nTracks);

        obj->tags = (char **) malloc(sizeof(char *) * nTracks);

        for (iTrack = 0; iTrack < nTracks; iTrack++) {

            obj->tags[iTrack] = (char *) malloc(sizeof(char) * 256);
            strcpy(obj->tags[iTrack], "");

        }

        obj->activity = (float *) malloc(sizeof(float) * nTracks);
        memset(obj->activity, 0x00, sizeof(float) * nTracks);

        return obj;

    }

    void tracks_destroy(tracks_obj * obj) {

        unsigned int iTrack;

        free((void *) obj->array);
        free((void *) obj->ids);

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {
            free((void *) obj->tags[iTrack]);
        }
        free((void *) obj->tags);

        free((void *) obj->activity);
        free((void *) obj);

    }

    tracks_obj * tracks_clone(const tracks_obj * obj) {

        tracks_obj * clone;
        unsigned int iTrack;

        clone = (tracks_obj *) malloc(sizeof(tracks_obj));

        clone->nTracks = obj->nTracks;
        clone->array = (float *) malloc(sizeof(float) * 3 * obj->nTracks);
        memcpy(clone->array, obj->array, sizeof(float) * 3 * obj->nTracks);
        clone->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracks);
        memcpy(clone->ids, obj->ids, sizeof(unsigned long long) * obj->nTracks);

        clone->tags = (char **) malloc(sizeof(char *) * obj->nTracks);

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            clone->tags[iTrack] = (char *) malloc(sizeof(char) * 256);
            strcpy(clone->tags[iTrack], "");
            
        }

        clone->activity = (float *) malloc(sizeof(float) * obj->nTracks);
        memcpy(clone->activity, obj->activity, sizeof(float) * obj->nTracks);

        return clone;

    }

    void tracks_copy(tracks_obj * dest, const tracks_obj * src) {

        unsigned int iTrack;

        dest->nTracks = src->nTracks;
        memcpy(dest->array, src->array, sizeof(float) * 3 * src->nTracks);
        memcpy(dest->ids, src->ids, sizeof(unsigned long long) * src->nTracks);
        
        for (iTrack = 0; iTrack < src->nTracks; iTrack++) {

            strcpy(dest->tags[iTrack], src->tags[iTrack]);

        }

        memcpy(dest->activity, src->activity, sizeof(float) * src->nTracks);

    }

    void tracks_zero(tracks_obj * obj) {

        unsigned int iTrack;

        memset(obj->array, 0x00, sizeof(float) * 3 * obj->nTracks);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * obj->nTracks);       

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {
            
            strcpy(obj->tags[iTrack], "");

        }

        memset(obj->activity, 0x00, sizeof(float) * obj->nTracks);

    }

    void tracks_printf(const tracks_obj * obj) {

        unsigned int iTrack;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("(%04llu)-[%s]: %+1.3f %+1.3f %+1.3f - %1.3f\n",
                   obj->ids[iTrack],
                   obj->tags[iTrack],
                   obj->array[iTrack * 3 + 0],
                   obj->array[iTrack * 3 + 1],
                   obj->array[iTrack * 3 + 2],
                   obj->activity[iTrack]);
            
        }

    }
