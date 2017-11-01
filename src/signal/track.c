    
    #include "track.h"

    tracks_obj * tracks_construct_zero(const unsigned int nTracks) {

        tracks_obj * obj;

        obj = (tracks_obj *) malloc(sizeof(tracks_obj));

        obj->nTracks = nTracks;
        obj->array = (float *) malloc(sizeof(float) * 3 * nTracks);
        memset(obj->array, 0x00, sizeof(float) * 3 * nTracks);
        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * nTracks);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * nTracks);
        obj->activity = (float *) malloc(sizeof(float) * nTracks);
        memset(obj->activity, 0x00, sizeof(float) * nTracks);

        return obj;

    }

    void tracks_destroy(tracks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->ids);
        free((void *) obj->activity);
        free((void *) obj);

    }

    tracks_obj * tracks_clone(const tracks_obj * obj) {

        tracks_obj * clone;

        clone = (tracks_obj *) malloc(sizeof(tracks_obj));

        clone->nTracks = obj->nTracks;
        clone->array = (float *) malloc(sizeof(float) * 3 * obj->nTracks);
        memcpy(clone->array, obj->array, sizeof(float) * 3 * obj->nTracks);
        clone->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracks);
        memcpy(clone->ids, obj->ids, sizeof(unsigned long long) * obj->nTracks);
        clone->activity = (float *) malloc(sizeof(float) * obj->nTracks);
        memcpy(clone->activity, obj->activity, sizeof(float) * obj->nTracks);

        return clone;

    }

    void tracks_copy(tracks_obj * dest, const tracks_obj * src) {

        dest->nTracks = src->nTracks;
        memcpy(dest->array, src->array, sizeof(float) * 3 * src->nTracks);
        memcpy(dest->ids, src->ids, sizeof(unsigned long long) * src->nTracks);
        memcpy(dest->activity, src->activity, sizeof(float) * src->nTracks);

    }

    void tracks_zero(tracks_obj * obj) {

        obj->nTracks = 0;
        memset(obj->array, 0x00, sizeof(float) * 3 * obj->nTracks);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * obj->nTracks);
        memset(obj->activity, 0x00, sizeof(float) * obj->nTracks);

    }

    void tracks_printf(const tracks_obj * obj) {

        unsigned int iTrack;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("(%04llu): %+1.3f %+1.3f %+1.3f - %1.3f\n",
                   obj->ids[iTrack],
                   obj->array[iTrack * 3 + 0],
                   obj->array[iTrack * 3 + 1],
                   obj->array[iTrack * 3 + 2],
                   obj->activity[iTrack]);
            
        }


    }