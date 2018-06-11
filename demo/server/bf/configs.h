#ifndef __ODASSERVERBF_CONFIGS
#define __ODASSERVERBF_CONFIGS

    #include <odas/odas.h>
    #include <stdlib.h>

    typedef struct configs {

        dsr_hops_cfg * dsr_hops_in_config;
        dsr_targets_cfg * dsr_targets_in_config;

        msg_hops_cfg * msg_hops_in_config;
        mod_stft_cfg * mod_stft_in_config;
        msg_spectra_cfg * msg_spectra_in_config;
        msg_targets_cfg * msg_targets_in_config;

        mod_tt_cfg * mod_tt_config;
        mod_bf_cfg * mod_bf_config;
        
        msg_tracks_cfg * msg_tracks_out_config;
        msg_spectra_cfg * msg_spectra_out_config;
        mod_istft_cfg * mod_istft_out_config;
        msg_hops_cfg * msg_hops_out_config;

        ser_hops_cfg * ser_hops_out_config;
        ser_tracks_cfg * ser_tracks_out_config;

    } configs;

    configs * configs_construct(void);

    void configs_destroy(configs * cfgs);



#endif