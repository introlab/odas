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

        float mod_noise_mics_prf;
        float con_powers_mics_prf;

        float mod_ssl_prf;
        float con_pots_ssl_prf;
        float snk_pots_ssl_prf;

        float inj_targets_sst_prf;
        float con_targets_sst_prf;

        float mod_sst_prf;
        float con_tracks_sst_prf;
        float snk_tracks_sst_prf;

        float mod_sss_prf;
        float con_spectra_seps_prf;
        float con_spectra_pfs_prf;

        float mod_istft_seps_prf;
        float mod_istft_pfs_prf;
        float con_hops_seps_prf;
        float con_hops_pfs_prf;

        float mod_resample_seps_prf;
        float mod_resample_pfs_prf;
        float con_hops_seps_rs_prf;
        float con_hops_pfs_rs_prf;

        float mod_volume_seps_prf;
        float mod_volume_pfs_prf;
        float con_hops_seps_vol_prf;
        float con_hops_pfs_vol_prf;
        float snk_hops_seps_vol_prf;
        float snk_hops_pfs_vol_prf;

        float mod_classify_prf;
        float con_categories_prf;
        float snk_categories_prf;

    } profiler;

    profiler * profiler_construct(void);

    void profiler_destroy(profiler * prf);

    void profiler_printf(const profiler * prf);

#endif