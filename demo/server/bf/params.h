#ifndef __ODASSERVERBF_PARAMS
#define __ODASSERVERBF_PARAMS

	#include "configs.h"
	#include "settings.h"
	
	#include <odas/odas.h>
	#include <stdlib.h>
	#include <stdio.h>

	void params_process(const settings * sets, configs * cfgs);

    void params_dsr_hops_in(const settings * sets, dsr_hops_cfg * cfg);

    void params_dsr_targets_in(const settings * sets, dsr_targets_cfg * cfg);

    void params_msg_hops_in(const settings * sets, msg_hops_cfg * cfg);

    void params_mod_stft_in(const settings * sets, mod_stft_cfg * cfg);

    void params_msg_spectra_in(const settings * sets, msg_spectra_cfg * cfg);

    void params_msg_targets_in(const settings * sets, msg_targets_cfg * cfg);

    void params_mod_tt(const settings * sets, mod_tt_cfg * cfg);

    void params_mod_bf(const settings * sets, mod_bf_cfg * cfg);

    void params_msg_tracks_out(const settings * sets, msg_tracks_cfg * cfg);

    void params_msg_spectra_out(const settings * sets, msg_spectra_cfg * cfg);

    void params_mod_istft_out(const settings * sets, mod_istft_cfg * cfg);

    void params_msg_hops_out(const settings * sets, msg_hops_cfg * cfg);

    void params_ser_hops_out(const settings * sets, ser_hops_cfg * cfg);

    void params_ser_tracks_out(const settings * sets, ser_tracks_cfg * cfg);

#endif