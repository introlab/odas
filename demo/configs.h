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

        mod_ssl_cfg * mod_ssl_config;
        msg_pots_cfg * msg_pots_ssl_config;
        snk_pots_cfg * snk_pots_ssl_config;

        mod_sst_cfg * mod_sst_config;
        msg_tracks_cfg * msg_tracks_sst_config;
        snk_tracks_cfg * snk_tracks_sst_config;

    } configs;

    configs * configs_construct(const char * file_config);

    void configs_destroy(configs * cfgs);

#endif