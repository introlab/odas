#ifndef __ODAS_SYSTEM_DEMIXING2ENV
#define __ODAS_SYSTEM_DEMIXING2ENV

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/demixing.h"
    #include "../signal/env.h"
    #include "../signal/mask.h"
    #include "../signal/track.h"
    
    typedef struct demixing2env_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

    } demixing2env_obj;

    demixing2env_obj * demixing2env_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize);

    void demixing2env_destroy(demixing2env_obj * obj);

    void demixing2env_process(demixing2env_obj * obj, const tracks_obj * tracks, const demixings_obj * demixings, const masks_obj * masks, const envs_obj * envsChannel, envs_obj * envsSeparated);

#endif