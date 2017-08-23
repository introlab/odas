#ifndef __ODAS_SYSTEM_STEER2ENV
#define __ODAS_SYSTEM_STEER2ENV

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/env.h"
    #include "../signal/freq.h"
    #include "../signal/mask.h"
    #include "../signal/steer.h"
    #include "../signal/track.h"

    typedef struct steer2env_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

    } steer2env_obj;    

    steer2env_obj * steer2env_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize);

    void steer2env_destroy(steer2env_obj * obj);

    void steer2env_process(steer2env_obj * obj, const tracks_obj * tracks, const steers_obj * demixing, const masks_obj * masks, const freqs_obj * freqs, envs_obj * envs);

#endif