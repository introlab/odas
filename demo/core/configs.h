#ifndef __ODAS_DEMO_CORE_CONFIGS
#define __ODAS_DEMO_CORE_CONFIGS

    #include <odas/odas.h>
    #include <stdlib.h>

    typedef struct configs {

        src_hops_cfg * src_hops_in_raw_config;
        msg_hops_cfg * msg_hops_in_raw_config;
        snk_hops_cfg * snk_hops_in_raw_config;

        src_targets_cfg * src_targets_in_raw_config;
        msg_targets_cfg * msg_targets_in_raw_config;

        mod_mapping_cfg * mod_mapping_in_config;
        msg_hops_cfg * msg_hops_in_map_config;

        mod_resample_cfg * mod_resample_in_config;
        msg_hops_cfg * msg_hops_in_rs_config;

        mod_align_cfg * mod_align_in_config;
        msg_targets_cfg * msg_targets_in_rs_config;

        mod_stft_cfg * mod_stft_in_config;
        msg_spectra_cfg * msg_spectra_in_config;

        mod_noise_cfg * mod_noise_in_config;
        msg_powers_cfg * msg_powers_in_config;

        mod_ssl_cfg * mod_ssl_config;
        msg_pots_cfg * msg_pots_config;
        snk_pots_cfg * snk_pots_config;

        mod_sst_cfg * mod_sst_config;
        msg_tracks_cfg * msg_tracks_config;
        snk_tracks_cfg * snk_tracks_config;

        mod_lag_cfg * mod_lag_config;
        msg_spectra_cfg * msg_spectra_lag_config;

        mod_sss_cfg * mod_sss_config;
        msg_spectra_cfg * msg_spectra_out_sep_config;
        msg_spectra_cfg * msg_spectra_out_pf_config;

        mod_istft_cfg * mod_istft_out_sep_config;
        msg_hops_cfg * msg_hops_out_sep_config;
        mod_resample_cfg * mod_resample_out_seprs_config;
        msg_hops_cfg * msg_hops_out_seprs_config;
        snk_hops_cfg * snk_hops_out_seprs_config;

        mod_istft_cfg * mod_istft_out_pf_config;
        msg_hops_cfg * msg_hops_out_pf_config;
        mod_resample_cfg * mod_resample_out_pfrs_config;
        msg_hops_cfg * msg_hops_out_pfrs_config;
        snk_hops_cfg * snk_hops_out_pfrs_config;

    } configs;

    configs * configs_construct(void);

    void configs_destroy(configs * cfgs);

#endif