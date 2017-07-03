#ifndef __DEMO_CONFIGS
#define __DEMO_CONFIGS

    #include "parameters.h"

    #include <odas/odas.h>
    #include <stdlib.h>

    typedef struct configs {
                
        src_hops_cfg * src_hops_raw_config;
        msg_hops_cfg * msg_hops_raw_config;
        unsigned int snk_hops_raw_config_count;                
        snk_hops_cfg ** snk_hops_raw_configs;       

        mod_mapping_cfg * mod_mapping_config;
        msg_hops_cfg * msg_hops_mapping_config;
        unsigned int snk_hops_mapping_config_count;
        snk_hops_cfg ** snk_hops_mapping_configs;

        mod_resample_cfg * mod_resample_config;
        msg_hops_cfg * msg_hops_resample_config;
        unsigned int snk_hops_resample_config_count;
        snk_hops_cfg ** snk_hops_resample_configs;

        mod_stft_cfg * mod_stft_config;
        msg_spectra_cfg * msg_spectra_stft_config;
        unsigned int snk_spectra_stft_config_count;
        snk_spectra_cfg ** snk_spectra_stft_configs;

        mod_ssl_cfg * mod_ssl_config;
        msg_pots_cfg * msg_pots_ssl_config;
        unsigned int snk_pots_ssl_config_count;
        snk_pots_cfg ** snk_pots_ssl_configs;

        mod_sst_cfg * mod_sst_config;
        msg_tracks_cfg * msg_tracks_sst_config;
        unsigned int snk_tracks_sst_config_count;
        snk_tracks_cfg ** snk_tracks_sst_configs;

        mod_sss_cfg * mod_sss_config;
        msg_spectra_cfg * msg_spectra_sss_config;
        unsigned int snk_spectra_sss_config_count;
        snk_spectra_cfg ** snk_spectra_sss_configs;

        mod_sspf_cfg * mod_sspf_config;
        msg_spectra_cfg * msg_spectra_sspf_config;
        unsigned int snk_spectra_sspf_config_count;
        snk_spectra_cfg ** snk_spectra_sspf_configs;

    } configs;

    configs * configs_construct(const char * file_config, const char * file_ios);

    void configs_destroy(configs * cfgs);

#endif