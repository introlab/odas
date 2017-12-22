#ifndef __DEMO_CONFIGS
#define __DEMO_CONFIGS

    #include "parameters.h"

    #include <odas/odas.h>
    #include <stdlib.h>

    typedef struct configs {
                
        src_hops_cfg * src_hops_mics_config;
        msg_hops_cfg * msg_hops_mics_raw_config;

        mod_mapping_cfg * mod_mapping_mics_config;
        msg_hops_cfg * msg_hops_mics_map_config;

        mod_resample_cfg * mod_resample_mics_config;
        msg_hops_cfg * msg_hops_mics_rs_config;

        mod_stft_cfg * mod_stft_mics_config;
        msg_spectra_cfg * msg_spectra_mics_config;

        mod_noise_cfg * mod_noise_mics_config;
        msg_powers_cfg * msg_powers_mics_config;

        mod_ssl_cfg * mod_ssl_config;
        msg_pots_cfg * msg_pots_ssl_config;
        snk_pots_cfg * snk_pots_ssl_config;

        inj_targets_cfg * inj_targets_sst_config;
        msg_targets_cfg * msg_targets_sst_config;

        mod_sst_cfg * mod_sst_config;
        msg_tracks_cfg * msg_tracks_sst_config;
        snk_tracks_cfg * snk_tracks_sst_config;

        mod_sss_cfg * mod_sss_config;
        msg_spectra_cfg * msg_spectra_seps_config;
        msg_spectra_cfg * msg_spectra_pfs_config;

        mod_istft_cfg * mod_istft_seps_config;
        mod_istft_cfg * mod_istft_pfs_config;
        msg_hops_cfg * msg_hops_seps_config;
        msg_hops_cfg * msg_hops_pfs_config;

        mod_resample_cfg * mod_resample_seps_config;
        mod_resample_cfg * mod_resample_pfs_config;
        msg_hops_cfg * msg_hops_seps_rs_config;
        msg_hops_cfg * msg_hops_pfs_rs_config;

        mod_volume_cfg * mod_volume_seps_config;
        mod_volume_cfg * mod_volume_pfs_config;
        msg_hops_cfg * msg_hops_seps_vol_config;
        msg_hops_cfg * msg_hops_pfs_vol_config;
        snk_hops_cfg * snk_hops_seps_vol_config;
        snk_hops_cfg * snk_hops_pfs_vol_config;

        mod_classify_cfg * mod_classify_config;
        msg_categories_cfg * msg_categories_config;
        snk_categories_cfg * snk_categories_config;

    } configs;

    configs * configs_construct(const char * file_config);

    void configs_destroy(configs * cfgs);

#endif