#ifndef __ODAS_SYSTEM_TRACK2STEER
#define __ODAS_SYSTEM_TRACK2STEER

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/gain.h"
    #include "../signal/mask.h"
    #include "../signal/track.h"
    #include "../signal/steer.h"
    
    typedef struct track2steer_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;
        float c;
        unsigned int fS;
        float * mics;

        float * factor;
        float speed;

    } track2steer_obj;    

    track2steer_obj * track2steer_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float c, const unsigned int fS, const float * mics);

    void track2steer_destroy(track2steer_obj * obj);

    void track2steer_process(track2steer_obj * obj, const tracks_obj * tracks, const gains_obj * gains, const masks_obj * masks, steers_obj * steers);    

#endif