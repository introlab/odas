
    #include "configs.h"

    configs * configs_construct(void) {

        configs * cfgs;

        cfgs = (configs *) malloc(sizeof(configs));

        cfgs->src_hops_in_raw_config = src_hops_cfg_construct();
        cfgs->msg_hops_in_raw_config = msg_hops_cfg_construct();
        cfgs->snk_hops_in_raw_config = snk_hops_cfg_construct();

        cfgs->src_targets_in_raw_config = src_targets_cfg_construct();
        cfgs->msg_targets_in_raw_config = msg_targets_cfg_construct();

        cfgs->mod_mapping_in_config = mod_mapping_cfg_construct();
        cfgs->msg_hops_in_map_config = msg_hops_cfg_construct();

        cfgs->mod_resample_in_config = mod_resample_cfg_construct();
        cfgs->msg_hops_in_rs_config = msg_hops_cfg_construct();

        cfgs->mod_align_in_config = mod_align_cfg_construct();
        cfgs->msg_targets_in_rs_config = msg_targets_cfg_construct();

        cfgs->mod_stft_in_config = mod_stft_cfg_construct();
        cfgs->msg_spectra_in_config = msg_spectra_cfg_construct();

        cfgs->mod_noise_in_config = mod_noise_cfg_construct();
        cfgs->msg_powers_in_config = msg_powers_cfg_construct();

        cfgs->mod_ssl_config = mod_ssl_cfg_construct();
        cfgs->msg_pots_config = msg_pots_cfg_construct();
        cfgs->snk_pots_config = snk_pots_cfg_construct();

        cfgs->mod_sst_config = mod_sst_cfg_construct();
        cfgs->msg_tracks_config = msg_tracks_cfg_construct();
        cfgs->snk_tracks_config = snk_tracks_cfg_construct();

        cfgs->mod_lag_config = mod_lag_cfg_construct();
        cfgs->msg_spectra_lag_config = msg_spectra_cfg_construct();

        cfgs->mod_sss_config = mod_sss_cfg_construct();
        cfgs->msg_spectra_out_sep_config = msg_spectra_cfg_construct();
        cfgs->msg_spectra_out_pf_config = msg_spectra_cfg_construct();

        cfgs->mod_istft_out_sep_config = mod_istft_cfg_construct();
        cfgs->msg_hops_out_sep_config = msg_hops_cfg_construct();
        cfgs->mod_resample_out_seprs_config = mod_resample_cfg_construct();
        cfgs->msg_hops_out_seprs_config = msg_hops_cfg_construct();
        cfgs->snk_hops_out_seprs_config = snk_hops_cfg_construct();

        cfgs->mod_istft_out_pf_config = mod_istft_cfg_construct();
        cfgs->msg_hops_out_pf_config = msg_hops_cfg_construct();
        cfgs->mod_resample_out_pfrs_config = mod_resample_cfg_construct();
        cfgs->msg_hops_out_pfrs_config = msg_hops_cfg_construct();
        cfgs->snk_hops_out_pfrs_config = snk_hops_cfg_construct();

        return cfgs;

    }

    void configs_destroy(configs * cfgs) {

        src_hops_cfg_destroy(cfgs->src_hops_in_raw_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_in_raw_config);
        snk_hops_cfg_destroy(cfgs->snk_hops_in_raw_config);

        src_targets_cfg_destroy(cfgs->src_targets_in_raw_config);
        msg_targets_cfg_destroy(cfgs->msg_targets_in_raw_config);

        mod_mapping_cfg_destroy(cfgs->mod_mapping_in_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_in_map_config);

        mod_resample_cfg_destroy(cfgs->mod_resample_in_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_in_rs_config);

        mod_align_cfg_destroy(cfgs->mod_align_in_config);
        msg_targets_cfg_destroy(cfgs->msg_targets_in_rs_config);

        mod_stft_cfg_destroy(cfgs->mod_stft_in_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_in_config);

        mod_noise_cfg_destroy(cfgs->mod_noise_in_config);
        msg_powers_cfg_destroy(cfgs->msg_powers_in_config);

        mod_ssl_cfg_destroy(cfgs->mod_ssl_config);
        msg_pots_cfg_destroy(cfgs->msg_pots_config);
        snk_pots_cfg_destroy(cfgs->snk_pots_config);

        mod_sst_cfg_destroy(cfgs->mod_sst_config);
        msg_tracks_cfg_destroy(cfgs->msg_tracks_config);
        snk_tracks_cfg_destroy(cfgs->snk_tracks_config);

        mod_lag_cfg_destroy(cfgs->mod_lag_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_lag_config);

        mod_sss_cfg_destroy(cfgs->mod_sss_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_out_sep_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_out_pf_config);

        mod_istft_cfg_destroy(cfgs->mod_istft_out_sep_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_out_sep_config);
        mod_resample_cfg_destroy(cfgs->mod_resample_out_seprs_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_out_seprs_config);
        snk_hops_cfg_destroy(cfgs->snk_hops_out_seprs_config);

        mod_istft_cfg_destroy(cfgs->mod_istft_out_pf_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_out_pf_config);
        mod_resample_cfg_destroy(cfgs->mod_resample_out_pfrs_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_out_pfrs_config);
        snk_hops_cfg_destroy(cfgs->snk_hops_out_pfrs_config);

        free((void *) cfgs);

    }
