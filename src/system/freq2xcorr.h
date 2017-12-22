#ifndef __ODAS_SYSTEM_FREQ2XCORR
#define __ODAS_SYSTEM_FREQ2XCORR

    #include "../signal/frame.h"
    #include "../signal/freq.h"
    #include "../signal/pair.h"
    #include "../signal/tdoa.h"
    #include "../signal/xcorr.h"
    #include "../utils/fft.h"

    typedef struct freq2xcorr_obj {

        unsigned int frameSize;
        unsigned int halfFrameSize;

        float * frame;

        fft_obj * fft;

    } freq2xcorr_obj;

    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    void freq2xcorr_destroy(freq2xcorr_obj * obj);

    void freq2xcorr_process(freq2xcorr_obj * obj, const freqs_obj * freqs, const pairs_obj * pairs, xcorrs_obj * xcorrs);

#endif