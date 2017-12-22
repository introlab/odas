#ifndef __ODAS_SYSTEM_ACORR2PITCH
#define __ODAS_SYSTEM_ACORR2PITCH

    #include "../signal/acorr.h"
    #include "../signal/pitch.h"

    #include <math.h>

    typedef struct acorr2pitch_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        unsigned int frameSize;
        unsigned int winSize;

    } acorr2pitch_obj;

    acorr2pitch_obj * acorr2pitch_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize, const unsigned int winSize);

    void acorr2pitch_destroy(acorr2pitch_obj * obj);

    void acorr2pitch_process(acorr2pitch_obj * obj, const acorrs_obj * acorrs, pitches_obj * pitches);

#endif