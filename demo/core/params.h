#ifndef __ODAS_DEMO_CORE_PARAMETERS
#define __ODAS_DEMO_CORE_PARAMETERS

    #include <odas/odas.h>
    #include "configs.h"
    #include "settings.h"
    #include "sockets.h"
    #include <math.h>
    
    void params_process(const settings * sets, const sockets * scks, configs * cfgs);

    void params_process_src_hops(const sockets * scks, src_hops_cfg * cfg);

    void params_process_msg_hops(const settings * sets, msg_hops_cfg * cfg);

    void params_process_snk_hops(const sockets * scks, snk_hops_cfg * cfg);

    void params_process_src_targets(const sockets * scks, src_targets_cfg * cfg);

    void params_process_msg_targets(const settings * sets, msg_targets_cfg * cfg);

    void params_process_snk_targets(const sockets * scks, snk_targets_cfg * cfg);

    void params_process_mod_stft(const settings * sets, mod_stft_cfg * cfg);

    void params_process_msg_spectra(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_noise(const settings * sets, mod_noise_cfg * cfg);

    void params_process_msg_powers(const settings * sets, msg_powers_cfg * cfg);

    void params_process_mod_ssl(const settings * sets, mod_ssl_cfg * cfg);

    void params_process_msg_pots(const settings * sets, msg_pots_cfg * cfg);

    void params_process_snk_pots(const sockets * scks, snk_pots_cfg * cfg);

    void params_process_mod_sst(const settings * sets, mod_sst_cfg * cfg);

    void params_process_msg_tracks(const settings * sets, msg_tracks_cfg * cfg);

    void params_process_snk_tracks(const sockets * scks, snk_tracks_cfg * cfg);

    void params_process_mod_lag(const settings * sets, mod_lag_cfg * cfg);

    void params_process_msg_spectra_lag(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_sss(const settings * sets, mod_sss_cfg * cfg);

    void params_process_msg_spectra_sep(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_istft_sep(const settings * sets, mod_istft_cfg * cfg);

    void params_process_msg_hops_sep(const settings * sets, msg_hops_cfg * cfg);

    void params_process_snk_hops_sep(const sockets * scks, snk_hops_cfg * cfg);

    void params_process_msg_spectra_pf(const settings * sets, msg_spectra_cfg * cfg);

    void params_process_mod_istft_pf(const settings * sets, mod_istft_cfg * cfg);

    void params_process_msg_hops_pf(const settings * sets, msg_hops_cfg * cfg);

    void params_process_snk_hops_pf(const sockets * scks, snk_hops_cfg * cfg);

#endif
