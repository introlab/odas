#ifndef __DEMO_PROFILER
#define __DEMO_PROFILER

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    typedef struct profiler {

        float duration;

        float src_hops_mics_prf;
        float con_hops_mics_raw_prf;

        float mod_mapping_mics_prf;
        float con_hops_mics_map_prf;

        float mod_resample_mics_prf;
        float con_hops_mics_rs_prf;

        float mod_stft_mics_prf;
        float con_spectra_mics_prf;

        float mod_ssl_prf;
        float con_pots_ssl_prf;
        float snk_pots_ssl_prf;

        float mod_sst_prf;
        float con_tracks_sst_prf;
        float snk_tracks_sst_prf;

    } profiler;

    profiler * profiler_construct(void);

    void profiler_destroy(profiler * prf);

    void profiler_printf(const profiler * prf);

#endif