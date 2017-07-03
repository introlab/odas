#ifndef __ODAS_SYSTEM_GAIN2MASK
#define __ODAS_SYSTEM_GAIN2MASK

    #include "../signal/gain.h"
    #include "../signal/mask.h"

    #include <stdlib.h>
    #include <string.h>

    typedef struct gain2mask_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float gainMin;

    } gain2mask_obj;

    gain2mask_obj * gain2mask_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float gainMin);

    void gain2mask_destroy(gain2mask_obj * obj);

    void gain2mask_process(gain2mask_obj * obj, const gains_obj * gains, masks_obj * masks);

#endif