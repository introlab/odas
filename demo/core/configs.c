
    #include "configs.h"

    configs * configs_construct(void) {

        configs * cfgs;

        cfgs = (configs *) malloc(sizeof(configs));

        cfgs->src_hops_config = src_hops_cfg_construct();
        cfgs->msg_hops_config = msg_hops_cfg_construct();
        cfgs->snk_hops_config = snk_hops_cfg_construct();

        cfgs->src_targets_config = src_targets_cfg_construct();
        cfgs->msg_targets_config = msg_targets_cfg_construct();
        cfgs->snk_targets_config = snk_targets_cfg_construct();

        cfgs->mod_stft_config = mod_stft_cfg_construct();
        cfgs->msg_spectra_config = msg_spectra_cfg_construct();

        cfgs->mod_ssl_config = mod_ssl_cfg_construct();
        cfgs->msg_pots_config = msg_pots_cfg_construct();
        cfgs->snk_pots_config = snk_pots_cfg_construct();

        cfgs->mod_sst_config = mod_sst_cfg_construct();
        cfgs->msg_tracks_config = msg_tracks_cfg_construct();
        cfgs->snk_tracks_config = snk_tracks_cfg_construct();

        cfgs->mod_lag_config = mod_lag_cfg_construct();
        cfgs->msg_spectra_delay_config = msg_spectra_cfg_construct();
        cfgs->mod_noise_delay_config = mod_noise_cfg_construct();
        cfgs->msg_powers_delay_config = msg_powers_cfg_construct();

        cfgs->mod_sss_config = mod_sss_cfg_construct();

        cfgs->msg_spectra_sep_config = msg_spectra_cfg_construct();
        cfgs->mod_istft_sep_config = mod_istft_cfg_construct();
        cfgs->msg_hops_sep_config = msg_hops_cfg_construct();
        cfgs->snk_hops_sep_config = snk_hops_cfg_construct();

        cfgs->msg_spectra_pf_config = msg_spectra_cfg_construct();
        cfgs->mod_istft_pf_config = mod_istft_cfg_construct();
        cfgs->msg_hops_pf_config = msg_hops_cfg_construct();
        cfgs->snk_hops_pf_config = snk_hops_cfg_construct();

        return cfgs;

    }

    void configs_destroy(configs * cfgs) {

        src_hops_cfg_destroy(cfgs->src_hops_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_config);
        snk_hops_cfg_destroy(cfgs->snk_hops_config);

        src_targets_cfg_destroy(cfgs->src_targets_config);
        msg_targets_cfg_destroy(cfgs->msg_targets_config);
        snk_targets_cfg_destroy(cfgs->snk_targets_config);

        mod_stft_cfg_destroy(cfgs->mod_stft_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_config);

        mod_ssl_cfg_destroy(cfgs->mod_ssl_config);
        msg_pots_cfg_destroy(cfgs->msg_pots_config);
        snk_pots_cfg_destroy(cfgs->snk_pots_config);

        mod_sst_cfg_destroy(cfgs->mod_sst_config);
        msg_tracks_cfg_destroy(cfgs->msg_tracks_config);
        snk_tracks_cfg_destroy(cfgs->snk_tracks_config);

        mod_lag_cfg_destroy(cfgs->mod_lag_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_delay_config);
        mod_noise_cfg_destroy(cfgs->mod_noise_delay_config);
        msg_powers_cfg_destroy(cfgs->msg_powers_delay_config);

        mod_sss_cfg_destroy(cfgs->mod_sss_config);
        
        msg_spectra_cfg_destroy(cfgs->msg_spectra_sep_config);
        mod_istft_cfg_destroy(cfgs->mod_istft_sep_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_sep_config);
        snk_hops_cfg_destroy(cfgs->snk_hops_sep_config);

        msg_spectra_cfg_destroy(cfgs->msg_spectra_pf_config);
        mod_istft_cfg_destroy(cfgs->mod_istft_pf_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_pf_config);
        snk_hops_cfg_destroy(cfgs->snk_hops_pf_config);

        free((void *) cfgs);

    }
