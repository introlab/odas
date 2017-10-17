#ifndef __ODAS_MODULE_SSS
#define __ODAS_MODULE_SSS

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"
    #include "../general/spatialfilter.h"

    #include "../init/directivity.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_tracks.h"

    #include "../signal/beampattern.h"
    #include "../signal/steer.h"
    #include "../signal/gain.h"
    #include "../signal/demixing.h"

    #include "../system/demixing2freq.h"
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

        track2gain_obj * track2gain;
        gain2mask_obj * gain2mask;
        track2steer_obj * track2steer;

        steer2demixing_ds_obj * steer2demixing_ds;
        steer2demixing_gss_obj * steer2demixing_gss;
        steer2demixing_mvdr_obj * steer2demixing_mvdr;

        demixings_obj * demixingsPrev;
        demixings_obj * demixingsNow;

        demixing2freq_obj * demixing2freq;

        msg_spectra_obj * in1;
        msg_tracks_obj * in2;
        msg_spectra_obj * out1;
        msg_spectra_obj * out2;

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

    } mod_sss_cfg;

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_sss_destroy(mod_sss_obj * obj);

    int mod_sss_process(mod_sss_obj * obj);

    int mod_sss_process_dds(mod_sss_obj * obj);

    int mod_sss_process_dgss(mod_sss_obj * obj);

    int mod_sss_process_dmvdr(mod_sss_obj * obj);

    int mod_sss_process_mspf(mod_sss_obj * obj);

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out1, msg_spectra_obj * out2);

    void mod_sss_disconnect(mod_sss_obj * obj);

    mod_sss_cfg * mod_sss_cfg_construct(void);

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg);

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg);

#endif