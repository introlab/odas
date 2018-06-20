#ifndef __ODAS_DEMO_CORE_PARAMETERS
#define __ODAS_DEMO_CORE_PARAMETERS

    #include <odas/odas.h>
    #include "configs.h"
    #include "settings.h"
    #include <math.h>
    
    void params_process(const settings * sets, configs * cfgs);

    void params_process_src_hops_in_raw(const settings * sets, src_hops_cfg * cfg);

    void params_process_msg_hops_in_raw(const settings * sets, msg_hops_cfg * cfg);

    void params_process_snk_hops_in_raw(const settings * sets, snk_hops_cfg * cfg);

    void params_process_src_targets_in_raw(const settings * sets, src_targets_cfg * cfg);

    void params_process_msg_targets_in_raw(const settings * sets, msg_targets_cfg * cfg);

    void params_process_mod_mapping_in(const settings * sets, mod_mapping_cfg * cfg);

    void params_process_msg_hops_in_map(const settings * sets, msg_hops_cfg * cfg);

    void params_process_mod_resample_in(const settings * sets, mod_resample_cfg * cfg);

    void params_process_msg_hops_in_rs(const settings * sets, msg_hops_cfg * cfg);

    void params_process_mod_align_in(const settings * sets, mod_align_cfg * cfg);

    void params_process_msg_targets_in_rs(const settings * sets, msg_targets_cfg * cfg);

    void params_process_mod_stft_in(const settings * sets, mod_stft_cfg * cfg);

    void params_process_msg_spectra_in(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_noise_in(const settings * sets, mod_noise_cfg * cfg);

    void params_process_msg_powers_in(const settings * sets, msg_powers_cfg * cfg);

    void params_process_mod_ssl(const settings * sets, mod_ssl_cfg * cfg);

    void params_process_msg_pots(const settings * sets, msg_pots_cfg * cfg);

    void params_process_snk_pots(const settings * sets, snk_pots_cfg * cfg);

    void params_process_mod_sst(const settings * sets, mod_sst_cfg * cfg);

    void params_process_msg_tracks(const settings * sets, msg_tracks_cfg * cfg);

    void params_process_snk_tracks(const settings * sets, snk_tracks_cfg * cfg);

    void params_process_mod_lag(const settings * sets, mod_lag_cfg * cfg);

    void params_process_msg_spectra_lag(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_sss(const settings * sets, mod_sss_cfg * cfg);

    void params_process_msg_spectra_out_sep(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_msg_spectra_out_pf(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_istft_out_sep(const settings * sets, mod_istft_cfg * cfg);

    void params_process_msg_hops_out_sep(const settings * sets, msg_hops_cfg * cfg);

    void params_process_mod_resample_out_seprs(const settings * sets, mod_resample_cfg * cfg);

    void params_process_msg_hops_out_seprs(const settings * sets, msg_hops_cfg * cfg);

    void params_process_snk_hops_out_seprs(const settings * sets, snk_hops_cfg * cfg);

    void params_process_mod_istft_out_pf(const settings * sets, mod_istft_cfg * cfg);

    void params_process_msg_hops_out_pf(const settings * sets, msg_hops_cfg * cfg);

    void params_process_mod_resample_out_pfrs(const settings * sets, mod_resample_cfg * cfg);

    void params_process_msg_hops_out_pfrs(const settings * sets, msg_hops_cfg * cfg);

    void params_process_snk_hops_out_pfrs(const settings * sets, snk_hops_cfg * cfg);

#endif
