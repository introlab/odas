#ifndef __ODAS_MODULE_SSPF
#define __ODAS_MODULE_SSPF

    #include "../signal/beampattern.h"
    #include "../signal/freq.h"
    #include "../signal/gain.h"
    #include "../signal/mask.h"
    
    #include "../system/gain2mask.h"
    #include "../system/track2gain.h"
    #include "../system/freq2freq.h"

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"

    #include "../init/directivity.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_tracks.h"

    #include <stdlib.h>

    typedef struct mod_sspf_obj {

        unsigned int nChannels;
        unsigned int nSeps;

        beampatterns_obj * beampatterns;

        track2gain_obj * track2gain;
        gains_obj * gains;
        gain2mask_obj * gain2mask;
        masks_obj * masks;
        freq2freq_obj * freq2freq;

        msg_spectra_obj * in1;
        msg_spectra_obj * in2;
        msg_tracks_obj * in3;
        msg_spectra_obj * out;

    } mod_sspf_obj;

    typedef struct mod_sspf_cfg {
        
        mics_obj * mics;

        unsigned int nThetas;
        float gainMin;       

    } mod_sspf_cfg;

    mod_sspf_obj * mod_sspf_construct(const mod_sspf_cfg * mod_sspf_config, const msg_spectra_cfg * msg_spectra_config, const msg_tracks_cfg * msg_tracks_config);

    void mod_sspf_destroy(mod_sspf_obj * obj);

    int mod_sspf_process(mod_sspf_obj * obj);

    void mod_sspf_connect(mod_sspf_obj * obj, msg_spectra_obj * in1, msg_spectra_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out);

    void mod_sspf_disconnect(mod_sspf_obj * obj);

    mod_sspf_cfg * mod_sspf_cfg_construct(void);

    void mod_sspf_cfg_destroy(mod_sspf_cfg * cfg);

    void mod_sspf_cfg_printf(const mod_sspf_cfg * cfg);

#endif