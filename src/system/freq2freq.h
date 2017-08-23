#ifndef __ODAS_SYSTEM_FREQ2FREQ
#define __ODAS_SYSTEM_FREQ2FREQ

    #include <stdlib.h>
    #include <math.h>

    #include "../signal/env.h"
    #include "../signal/freq.h"
    #include "../signal/gain.h"
    #include "../signal/mask.h"
    #include "../signal/pair.h"
    #include "../signal/track.h"
    
    typedef struct freq2freq_obj {

        unsigned int halfFrameSize;
        unsigned int lowPassCut;
        float epsilon;
        float alpha;
        float beta;
        float Ginterf;

    } freq2freq_obj;

    freq2freq_obj * freq2freq_construct_zero(const unsigned int halfFrameSize, const unsigned int lowPassCut, const float epsilon, const float alpha, const float beta, const float Ginterf);

    void freq2freq_destroy(freq2freq_obj * obj);

    void freq2freq_process_phasor(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors);

    void freq2freq_process_product(freq2freq_obj * obj, const freqs_obj * freqs1, const freqs_obj * freqs2, const pairs_obj * pairs, freqs_obj * freqs12);

    void freq2freq_process_lowpass(freq2freq_obj * obj, const freqs_obj * freqsAllPass, freqs_obj * freqsLowPass);

    void freq2freq_process_postfilter(freq2freq_obj * obj, const tracks_obj * tracks, const freqs_obj * freqsSeps, const envs_obj * envsSeps, const envs_obj * envsDiffuse, freqs_obj * freqsPosts);

#endif