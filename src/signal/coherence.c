
    #include "coherence.h"

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
