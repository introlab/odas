#ifndef __ODAS_SIGNAL_FREQ
#define __ODAS_SIGNAL_FREQ

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct freqs_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        float ** array;

    } freqs_obj;

    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    freqs_obj * freqs_clone(const freqs_obj * obj);

    void freqs_copy(freqs_obj * dest, const freqs_obj * src);

    void freqs_zero(freqs_obj * obj);

    void freqs_destroy(freqs_obj * obj);

    void freqs_printf(const freqs_obj * obj);

#endif