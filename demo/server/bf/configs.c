
    #include "configs.h"

    configs * configs_construct(void) {

        configs * cfgs;

        cfgs = (configs *) malloc(sizeof(configs));

        cfgs->dsr_hops_in_config = dsr_hops_cfg_construct();
        cfgs->dsr_targets_in_config = dsr_targets_cfg_construct();

        cfgs->msg_hops_in_config = msg_hops_cfg_construct();
        cfgs->mod_stft_in_config = mod_stft_cfg_construct();
        cfgs->msg_spectra_in_config = msg_spectra_cfg_construct();
        cfgs->msg_targets_in_config = msg_targets_cfg_construct();

        cfgs->mod_tt_config = mod_tt_cfg_construct();
        cfgs->mod_bf_config = mod_bf_cfg_construct();

        cfgs->msg_tracks_out_config = msg_tracks_cfg_construct();
        cfgs->msg_spectra_out_config = msg_spectra_cfg_construct();
        cfgs->mod_istft_out_config = mod_istft_cfg_construct();
        cfgs->msg_hops_out_config = msg_hops_cfg_construct();

        cfgs->ser_hops_out_config = ser_hops_cfg_construct();
        cfgs->ser_tracks_out_config = ser_tracks_cfg_construct();

        return cfgs;

    }

    void configs_destroy(configs * cfgs) {

        dsr_hops_cfg_destroy(cfgs->dsr_hops_in_config);
        dsr_targets_cfg_destroy(cfgs->dsr_targets_in_config);

        msg_hops_cfg_destroy(cfgs->msg_hops_in_config);
        mod_stft_cfg_destroy(cfgs->mod_stft_in_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_in_config);
        msg_targets_cfg_destroy(cfgs->msg_targets_in_config);

        mod_tt_cfg_destroy(cfgs->mod_tt_config);
        mod_bf_cfg_destroy(cfgs->mod_bf_config);

        msg_tracks_cfg_destroy(cfgs->msg_tracks_out_config);
        msg_spectra_cfg_destroy(cfgs->msg_spectra_out_config);
        mod_istft_cfg_destroy(cfgs->mod_istft_out_config);
        msg_hops_cfg_destroy(cfgs->msg_hops_out_config);

        ser_hops_cfg_destroy(cfgs->ser_hops_out_config);
        ser_tracks_cfg_destroy(cfgs->ser_tracks_out_config);

        free((void *) cfgs);

    }
