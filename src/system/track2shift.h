#ifndef __ODAS_SYSTEM_TRACK2SHIFT
#define __ODAS_SYSTEM_TRACK2SHIFT

    #include "../signal/track.h"
    #include "../signal/shift.h"

    typedef struct track2shift_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int fS;
        float c;
        float * mics;       

    } track2shift_obj;

    track2shift_obj * track2shift_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int fS, const unsigned int c, const float * mics);

    void track2shift_destroy(track2shift_obj * obj);

    void track2shift_process(track2shift_obj * obj, const tracks_obj * tracks, shifts_obj * shifts);

#endif