#ifndef __ODAS_SYSTEM_DEMIXING2FREQ
#define __ODAS_SYSTEM_DEMIXING2FREQ

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/demixing.h"
    #include "../signal/freq.h"
    #include "../signal/mask.h"
    #include "../signal/track.h"
    
    typedef struct demixing2freq_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

    } demixing2freq_obj;    

    demixing2freq_obj * demixing2freq_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize);

    void demixing2freq_destroy(demixing2freq_obj * obj);

    void demixing2freq_process(demixing2freq_obj * obj, const tracks_obj * tracks, const demixings_obj * demixings, const masks_obj * masks, const freqs_obj * freqsChannel, freqs_obj * freqsSeparated);

#endif