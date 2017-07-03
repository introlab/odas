#ifndef __ODAS_SYSTEM_SHIFT2FREQ
#define __ODAS_SYSTEM_SHIFT2FREQ

    #include "../signal/gain.h"
    #include "../signal/mask.h"
    #include "../signal/shift.h"
    #include "../signal/freq.h"

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    typedef struct shift2freq_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        float * array;

    } shift2freq_obj;

    shift2freq_obj * shift2freq_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize);

    void shift2freq_destroy(shift2freq_obj * obj);

    void shift2freq_process(shift2freq_obj * obj, const shifts_obj * shifts, const gains_obj * gains, const masks_obj * masks, freqs_obj * freqs);

#endif