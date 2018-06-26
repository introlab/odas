#ifndef __ODAS_DEMO_CORE_CONFIGS
#define __ODAS_DEMO_CORE_CONFIGS

    #include <odas/odas.h>
    #include <stdlib.h>

    typedef struct configs {

        src_hops_cfg * src_hops_config;
        msg_hops_cfg * msg_hops_config;
        snk_hops_cfg * snk_hops_config;

        src_targets_cfg * src_targets_config;
        msg_targets_cfg * msg_targets_config;
        snk_targets_cfg * snk_targets_config;

        mod_stft_cfg * mod_stft_config;
        msg_spectra_cfg * msg_spectra_config;

        mod_ssl_cfg * mod_ssl_config;
        msg_pots_cfg * msg_pots_config;
        snk_pots_cfg * snk_pots_config;

        mod_sst_cfg * mod_sst_config;
        msg_tracks_cfg * msg_tracks_config;
        snk_tracks_cfg * snk_tracks_config;

        mod_lag_cfg * mod_lag_config;
        msg_spectra_cfg * msg_spectra_delay_config;
        mod_noise_cfg * mod_noise_delay_config;
        msg_powers_cfg * msg_powers_delay_config;

        mod_sss_cfg * mod_sss_config;

        msg_spectra_cfg * msg_spectra_sep_config;
        mod_istft_cfg * mod_istft_sep_config;
        msg_hops_cfg * msg_hops_sep_config;
        snk_hops_cfg * snk_hops_sep_config;

        msg_spectra_cfg * msg_spectra_pf_config;
        mod_istft_cfg * mod_istft_pf_config;
        msg_hops_cfg * msg_hops_pf_config;
        snk_hops_cfg * snk_hops_pf_config;

    } configs;

    configs * configs_construct(void);

    void configs_destroy(configs * cfgs);

#endif