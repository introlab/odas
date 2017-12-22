    
    #include "gain.h"

    gains_obj * gains_construct_zero(const unsigned int nSeps, const unsigned int nChannels) {

        gains_obj * obj;

        obj = (gains_obj *) malloc(sizeof(gains_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        
        obj->array = (float *) malloc(sizeof(float) * nSeps * nChannels);
        memset(obj->array, 0x00, sizeof(float) * nSeps * nChannels);

        return obj;

    }

    void gains_destroy(gains_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void gains_printf(const gains_obj * obj) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("(%02u): ",iSep);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%+1.3f ",obj->array[iSep * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }