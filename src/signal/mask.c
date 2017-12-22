    
    #include "mask.h"

    masks_obj * masks_construct_zero(const unsigned int nSeps, const unsigned int nChannels) {

        masks_obj * obj;

        obj = (masks_obj *) malloc(sizeof(masks_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        
        obj->array = (char *) malloc(sizeof(char) * nSeps * nChannels);
        memset(obj->array, 0x00, sizeof(char) * nSeps * nChannels);

        return obj;

    }

    void masks_destroy(masks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void masks_printf(const masks_obj * obj) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("(%02u): ",iSep);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%d ",obj->array[iSep * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }