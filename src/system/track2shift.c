    
    #include "track2shift.h"

    track2shift_obj * track2shift_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int fS, const unsigned int c, const float * mics) {

        track2shift_obj * obj;

        obj = (track2shift_obj *) malloc(sizeof(track2shift_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->fS = fS;
        obj->c = c;

        obj->mics = (float *) malloc(sizeof(float) * nChannels * 3);
        memcpy(obj->mics, mics, sizeof(float) * nChannels * 3);

        return obj;

    }

    void track2shift_destroy(track2shift_obj * obj) {

        free((void *) obj->mics);
        free((void *) obj);

    }

    void track2shift_process(track2shift_obj * obj, const tracks_obj * tracks, shifts_obj * shifts) {

        unsigned int iSep;
        unsigned int iChannel;
        float dist;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    dist = tracks->array[iSep * 3 + 0] * obj->mics[iChannel * 3 + 0] + 
                           tracks->array[iSep * 3 + 1] * obj->mics[iChannel * 3 + 1] +
                           tracks->array[iSep * 3 + 2] * obj->mics[iChannel * 3 + 2]; 

                    shifts->array[iSep * obj->nChannels + iChannel] = -1.0f * (((float) obj->fS) / obj->c) * dist;

                }

            }
            else {

                memset(&(shifts->array[iSep * obj->nChannels]), 0x00, sizeof(float) * obj->nChannels);

            }

        }

    }