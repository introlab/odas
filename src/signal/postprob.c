
    #include "postprob.h"

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