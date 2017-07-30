#ifndef __ODAS_MODULE_SSS
#define __ODAS_MODULE_SSS

    #include "../signal/beampattern.h"
    #include "../signal/freq.h"
    #include "../signal/gain.h"
    #include "../signal/mask.h"
    #include "../signal/shift.h"
    
    #include "../system/gain2mask.h"
    #include "../system/track2gain.h"
    #include "../system/track2shift.h"
    #include "../system/freq2freq.h"

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"
    #include "../general/spatialfilter.h"

    #include "../init/directivity.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_tracks.h"

    #include <stdlib.h>

    typedef struct mod_sss_obj {

        unsigned int nChannels;
        unsigned int nSeps;

        beampatterns_obj * beampatterns_mics;
        beampatterns_obj * beampatterns_spatialfilter;

        track2shift_obj * track2shift;
        shifts_obj * shifts;
        track2gain_obj * track2gain;
        gains_obj * gains;
        gain2mask_obj * gain2mask;
        masks_obj * masks;
        freq2freq_obj * freq2freq;

        msg_spectra_obj * in1;
        msg_tracks_obj * in2;
        msg_spectra_obj * out;

    } mod_sss_obj;

    typedef struct mod_sss_cfg {
        
        mics_obj * mics;
        samplerate_obj * samplerate;
        soundspeed_obj * soundspeed; 
        spatialfilter_obj * spatialfilter;

        unsigned int nThetas;
        float gainMin;       

    } mod_sss_cfg;

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_spectra_cfg * msg_spectra_config, const msg_tracks_cfg * msg_tracks_config);

    void mod_sss_destroy(mod_sss_obj * obj);

    int mod_sss_process(mod_sss_obj * obj);

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out);

    void mod_sss_disconnect(mod_sss_obj * obj);

    mod_sss_cfg * mod_sss_cfg_construct(void);

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg);

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg);

#endif