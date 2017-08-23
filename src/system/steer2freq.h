#ifndef __ODAS_SYSTEM_STEER2FREQ
#define __ODAS_SYSTEM_STEER2FREQ

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/freq.h"
    #include "../signal/mask.h"
    #include "../signal/steer.h"
    #include "../signal/track.h"
    
    typedef struct steer2freq_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

    } steer2freq_obj;    

    steer2freq_obj * steer2freq_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize);

    void steer2freq_destroy(steer2freq_obj * obj);

    void steer2freq_process(steer2freq_obj * obj, const tracks_obj * tracks, const steers_obj * demixing, const masks_obj * masks, const freqs_obj * freqsChannel, freqs_obj * freqsSeparated);

#endif