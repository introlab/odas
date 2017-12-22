#ifndef __ODAS_SYSTEM_XCORR
#define __ODAS_SYSTEM_XCORR

    #include <stdlib.h>
    #include <string.h>

    #include "../signal/delta.h"
    #include "../signal/xcorr.h"
    #include "../signal/tdoa.h"
    #include "../signal/pair.h"

    typedef struct xcorr2xcorr_obj {

        unsigned int frameSize;     ///< Number of samples per frame.

    } xcorr2xcorr_obj;

    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize);

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj);

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const deltas_obj * deltas, const pairs_obj * pairs, xcorrs_obj * xcorrsMax);

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const tdoas_obj * tdoas, const deltas_obj * deltas, const pairs_obj * pairs, const unsigned int iPoint, xcorrs_obj * xcorrs);

#endif