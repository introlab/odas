#ifndef __ODAS_SIGNAL_ACORR
#define __ODAS_SIGNAL_ACORR

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct acorrs_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        float ** array;

    } acorrs_obj;

    acorrs_obj * acorrs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    void acorrs_destroy(acorrs_obj * obj);

    void acorrs_copy(acorrs_obj * dest, const acorrs_obj * src);

    void acorrs_zero(acorrs_obj * obj);

    void acorrs_printf(const acorrs_obj * obj);

#endif