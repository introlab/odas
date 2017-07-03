#ifndef __ODAS_SYSTEM_FREQ2FREQ
#define __ODAS_SYSTEM_FREQ2FREQ

    #include <stdlib.h>
    #include <math.h>

    #include "../signal/freq.h"
    #include "../signal/gain.h"
    #include "../signal/mask.h"
    #include "../signal/pair.h"
    #include "../signal/shift.h"
    
    typedef struct freq2freq_obj {

        unsigned int halfFrameSize;
        unsigned int lowPassCut;
        float epsilon;

    } freq2freq_obj;

    freq2freq_obj * freq2freq_construct_zero(const unsigned int halfFrameSize, const unsigned int lowPassCut, const float epsilon);

    void freq2freq_destroy(freq2freq_obj * obj);

    void freq2freq_process_phasor(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors);

    void freq2freq_process_product(freq2freq_obj * obj, const freqs_obj * freqs1, const freqs_obj * freqs2, const pairs_obj * pairs, freqs_obj * freqs12);

    void freq2freq_process_lowpass(freq2freq_obj * obj, const freqs_obj * freqsAllPass, freqs_obj * freqsLowPass);

    void freq2freq_process_delaysum(freq2freq_obj * obj, const freqs_obj * freqsChannels, const shifts_obj * shifts, const gains_obj * gains, const masks_obj * masks, freqs_obj * freqsSeps);

    void freq2freq_process_postfilter(freq2freq_obj * obj, const freqs_obj * freqsChannels, const freqs_obj * freqsSeps, const gains_obj * gains, const masks_obj * masks, freqs_obj * freqsPosts);

#endif