    
    #include "gain2mask.h"

    gain2mask_obj * gain2mask_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float gainMin) {

        gain2mask_obj * obj;

        obj = (gain2mask_obj *) malloc(sizeof(gain2mask_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->gainMin = gainMin;

        return obj;

    }

    void gain2mask_destroy(gain2mask_obj * obj) {

        free((void *) obj);

    }

    void gain2mask_process(gain2mask_obj * obj, const gains_obj * gains, masks_obj * masks) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                if (gains->array[iSep * obj->nChannels + iChannel] >= obj->gainMin) {
                    masks->array[iSep * obj->nChannels + iChannel] = 0x01;
                }
                else {
                    masks->array[iSep * obj->nChannels + iChannel] = 0x00;
                }

            }

        }

    }
