#ifndef __DEMO_PROFILER
#define __DEMO_PROFILER

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    typedef struct profiler {

        float duration;

        float src_hops_raw_prf;
        float con_hops_raw_prf;
        float snk_hops_raw_prf;

        float mod_mapping_prf;
        float con_hops_mapping_prf;
        float snk_hops_mapping_prf;

        float mod_resample_prf;
        float con_hops_resample_prf;
        float snk_hops_resample_prf;

        float mod_stft_prf;
        float con_spectra_stft_prf;
        float snk_spectra_stft_prf;

        float mod_ssl_prf;
        float con_pots_ssl_prf;
        float snk_pots_ssl_prf;

        float mod_sst_prf;
        float con_tracks_sst_prf;
        float snk_tracks_sst_prf;

        float mod_sss_prf;
        float con_spectra_sss_prf;
        float snk_spectra_sss_prf;

        float mod_sspf_prf;
        float con_spectra_sspf_prf;
        float snk_spectra_sspf_prf;

    } profiler;

    profiler * profiler_construct(void);

    void profiler_destroy(profiler * prf);

    void profiler_printf(const profiler * prf);

#endif