   
   /**
    * \file     track.c
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
