#ifndef __ODAS_MODULE_SSPF
#define __ODAS_MODULE_SSPF

    #include "../message/msg_envs.h"
    #include "../message/msg_spectra.h"
    #include "../message/msg_tracks.h"

    #include "../system/freq2env.h"
    #include "../signal/env.h"
    #include "../system/freq2freq.h"

    #include <stdlib.h>

    typedef struct mod_sspf_obj {

        unsigned int nSeps;
        unsigned int halfFrameSize;

        float alpha;
        float beta;
        float Ginterf;
        float epsilon;

        freq2env_obj * freq2env;
        envs_obj * envs;
        freq2freq_obj * freq2freq;

        msg_spectra_obj * in1;
        msg_envs_obj * in2;
        msg_tracks_obj * in3;
        msg_spectra_obj * out;

    } mod_sspf_obj;

    typedef struct mod_sspf_cfg {
        
        float alpha;
        float beta;
        float Ginterf;
        float epsilon;

    } mod_sspf_cfg;

    mod_sspf_obj * mod_sspf_construct(const mod_sspf_cfg * mod_sspf_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config, const msg_envs_cfg * msg_envs_config);

    void mod_sspf_destroy(mod_sspf_obj * obj);

    int mod_sspf_process(mod_sspf_obj * obj);

    void mod_sspf_connect(mod_sspf_obj * obj, msg_spectra_obj * in1, msg_envs_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out);

    void mod_sspf_disconnect(mod_sspf_obj * obj);

    mod_sspf_cfg * mod_sspf_cfg_construct(void);

    void mod_sspf_cfg_destroy(mod_sspf_cfg * cfg);

    void mod_sspf_cfg_printf(const mod_sspf_cfg * cfg);

#endif