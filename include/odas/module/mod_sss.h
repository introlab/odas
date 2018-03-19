#ifndef __ODAS_MODULE_SSS
#define __ODAS_MODULE_SSS

   /**
    * \file     mod_sss.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"
    #include "../general/spatialfilter.h"

    #include "../init/directivity.h"

    #include "../message/msg_powers.h"
    #include "../message/msg_spectra.h"
    #include "../message/msg_tracks.h"

    #include "../signal/beampattern.h"
    #include "../signal/steer.h"
    #include "../signal/gain.h"
    #include "../signal/demixing.h"
    #include "../signal/env.h"

    #include "../system/demixing2env.h"
    #include "../system/demixing2freq.h"
    #include "../system/env2env.h"
    #include "../system/freq2env.h"
    #include "../system/freq2freq.h"
    #include "../system/gain2mask.h"
    #include "../system/track2steer.h"
    #include "../system/track2gain.h"
    #include "../system/steer2demixing.h"

    #include <stdlib.h>
    #include <string.h>

    typedef struct mod_sss_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        char mode_sep;
        char mode_pf;

        beampatterns_obj * sep_ds_beampatterns_mics;
        beampatterns_obj * sep_ds_beampatterns_spatialfilter;
        steers_obj * sep_ds_steers;
        gains_obj * sep_ds_gains;
        masks_obj * sep_ds_masks;
        tracks_obj * sep_ds_tracksPrev;
        tracks_obj * sep_ds_tracksNow;
        track2gain_obj * sep_ds_track2gain;
        gain2mask_obj * sep_ds_gain2mask;
        track2steer_obj * sep_ds_track2steer;
        steer2demixing_ds_obj * sep_ds_steer2demixing;
        demixings_obj * sep_ds_demixingsPrev;
        demixings_obj * sep_ds_demixingsNow;
        demixing2freq_obj * sep_ds_demixing2freq;

        beampatterns_obj * sep_gss_beampatterns_mics;
        beampatterns_obj * sep_gss_beampatterns_spatialfilter;
        steers_obj * sep_gss_steers;
        gains_obj * sep_gss_gains;
        masks_obj * sep_gss_masks;
        tracks_obj * sep_gss_tracksPrev;
        tracks_obj * sep_gss_tracksNow;
        track2gain_obj * sep_gss_track2gain;
        gain2mask_obj * sep_gss_gain2mask;
        track2steer_obj * sep_gss_track2steer;
        steer2demixing_gss_obj * sep_gss_steer2demixing;
        demixings_obj * sep_gss_demixingsPrev;
        demixings_obj * sep_gss_demixingsNow;
        demixing2freq_obj * sep_gss_demixing2freq;

        masks_obj * sep_masks;
        demixings_obj * sep_demixings;

        freq2env_obj * pf_ms_freq2env;
        envs_obj * pf_ms_noisys;
        demixing2env_obj * pf_ms_demixing2env;
        envs_obj * pf_ms_noisesEst;
        env2env_mcra_obj * pf_ms_env2env_mcra;
        envs_obj * pf_ms_noisesSep;
        env2env_interf_obj * pf_ms_env2env_interf;
        envs_obj * pf_ms_interfs;
        env2env_gainspeech_obj * pf_ms_env2env_gainspeech;
        envs_obj * pf_ms_gainspeeches;
        envs_obj * pf_ms_snrs;
        envs_obj * pf_ms_vs;
        env2env_probspeech_obj * pf_ms_env2env_probspeech;
        envs_obj * pf_ms_probspeeches;
        env2env_gainall_obj * pf_ms_env2env_gainall;       
        envs_obj * pf_ms_gainalls;
        freq2freq_gain_obj * pf_ms_freq2freq_gain;

        freq2env_obj * pf_ss_freq2env_channels;
        envs_obj * pf_ss_env_channels;
        demixing2env_obj * pf_ss_demixing2env;
        envs_obj * pf_ss_env_channelseps;
        freq2env_obj * pf_ss_freq2env_seps;
        envs_obj * pf_ss_env_seps;
        env2env_gainratio_obj * pf_ss_env2env_gainratio;
        envs_obj * pf_ss_gainratio;
        freq2freq_gain_obj * pf_ss_freq2freq_gain;

        msg_spectra_obj * in1;
        msg_powers_obj * in2;
        msg_tracks_obj * in3;
        msg_spectra_obj * out1;
        msg_spectra_obj * out2;

        FILE * tmpFp;

    } mod_sss_obj;

    typedef struct mod_sss_cfg {

        char mode_sep;
        char mode_pf;

        unsigned int nThetas;
        float gainMin;

        float epsilon;

        mics_obj * mics;
        samplerate_obj * samplerate;
        soundspeed_obj * soundspeed;
        spatialfilter_obj * spatialfilter;    

        float sep_gss_lambda;
        float sep_gss_mu;

        unsigned int pf_ms_bSize;
        float pf_ms_alphaS;
        unsigned int pf_ms_L;
        float pf_ms_delta;
        float pf_ms_alphaD;

        float pf_ms_eta;
        float pf_ms_alphaZ;
        float pf_ms_alphaPmin;
        float pf_ms_thetaWin;
        float pf_ms_alphaWin;
        float pf_ms_maxAbsenceProb;
        float pf_ms_Gmin;
        unsigned int pf_ms_winSizeLocal;
        unsigned int pf_ms_winSizeGlobal;
        unsigned int pf_ms_winSizeFrame;

        float pf_ss_Gmin;
        float pf_ss_Gmid;
        float pf_ss_Gslope;

    } mod_sss_cfg;

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_sss_destroy(mod_sss_obj * obj);

    int mod_sss_process(mod_sss_obj * obj);

    int mod_sss_process_dds(mod_sss_obj * obj);

    int mod_sss_process_dgss(mod_sss_obj * obj);

    int mod_sss_process_sspf(mod_sss_obj * obj);

    int mod_sss_process_mspf(mod_sss_obj * obj);

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_powers_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out1, msg_spectra_obj * out2);

    void mod_sss_disconnect(mod_sss_obj * obj);

    mod_sss_cfg * mod_sss_cfg_construct(void);

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg);

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg);

#endif