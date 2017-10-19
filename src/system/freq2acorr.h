#ifndef __ODAS_SYSTEM_FREQ2ACORR
#define __ODAS_SYSTEM_FREQ2ACORR

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../signal/acorr.h"
    #include "../signal/freq.h"
    #include "../utils/fft.h"

    typedef struct freq2acorr_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        unsigned int frameSize;

        float * arrayIn;
        float * arrayOut;

        fft_obj * fft;

    } freq2acorr_obj;

    freq2acorr_obj * freq2acorr_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    void freq2acorr_destroy(freq2acorr_obj * obj);

    void freq2acorr_process(freq2acorr_obj * obj, const freqs_obj * freqs, acorrs_obj * acorrs);

#endif