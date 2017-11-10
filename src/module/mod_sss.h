#ifndef __ODAS_MODULE_SSS
#define __ODAS_MODULE_SSS

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

        beampatterns_obj * beampatterns_mics;
        beampatterns_obj * beampatterns_spatialfilter;
        steers_obj * steers;
        gains_obj * gains;
        masks_obj * masks;

        tracks_obj * tracksPrev;
        tracks_obj * tracksNow;

        track2gain_obj * track2gain;
        gain2mask_obj * gain2mask;
        track2steer_obj * track2steer;

        steer2demixing_ds_obj * steer2demixing_ds;
        steer2demixing_gss_obj * steer2demixing_gss;
        steer2demixing_mvdr_obj * steer2demixing_mvdr;

        demixings_obj * demixingsPrev;
        demixings_obj * demixingsNow;

        demixing2freq_obj * demixing2freq;

        freq2env_obj * freq2env;
        envs_obj * noisys;
        demixing2env_obj * demixing2env;
        envs_obj * noisesEst;
        env2env_mcra_obj * env2env_mcra;
        envs_obj * noisesSep;
        env2env_interf_obj * env2env_interf;
        envs_obj * interfs;
        env2env_gainspeech_obj * env2env_gainspeech;
        envs_obj * gainspeeches;
        envs_obj * snrs;
        envs_obj * vs;
        env2env_probspeech_obj * env2env_probspeech;
        envs_obj * probspeeches;
        env2env_gainall_obj * env2env_gainall;
        envs_obj * gainalls;
        freq2freq_gain_obj * freq2freq_gain;

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

        unsigned int pf_multi_bSize;
        float pf_multi_alphaS;
        unsigned int pf_multi_L;
        float pf_multi_delta;
        float pf_multi_alphaD;

        float pf_multi_eta;
        float pf_multi_alphaZ;
        float pf_multi_alphaPmin;
        float pf_multi_thetaWin;
        float pf_multi_alphaWin;
        float pf_multi_maxAbsenceProb;
        float pf_multi_Gmin;
        unsigned int pf_multi_winSizeLocal;
        unsigned int pf_multi_winSizeGlobal;
        unsigned int pf_multi_winSizeFrame;

    } mod_sss_cfg;

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_sss_destroy(mod_sss_obj * obj);

    int mod_sss_process(mod_sss_obj * obj);

    int mod_sss_process_dds(mod_sss_obj * obj);

    int mod_sss_process_dgss(mod_sss_obj * obj);

    int mod_sss_process_dmvdr(mod_sss_obj * obj);

    int mod_sss_process_mspf(mod_sss_obj * obj);

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_powers_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out1, msg_spectra_obj * out2);

    void mod_sss_disconnect(mod_sss_obj * obj);

    mod_sss_cfg * mod_sss_cfg_construct(void);

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg);

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg);

#endif