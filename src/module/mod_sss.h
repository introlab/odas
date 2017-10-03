#ifndef __ODAS_MODULE_SSS
#define __ODAS_MODULE_SSS

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"
    #include "../general/spatialfilter.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_tracks.h"

    #include "../system/track2steer.h"

    #include <stdlib.h>
    #include <string.h>

    typedef struct mod_sss_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        char mode_sep;
        char mode_pf;

        track2steer_obj * dds_track2steer;

    } mod_sss_obj;

    typedef struct mod_sss_cfg {

        char mode_sep;
        char mode_pf;

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

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out1, msg_spectra_obj * out2);

    void mod_sss_disconnect(mod_sss_obj * obj);

    mod_sss_cfg * mod_sss_cfg_construct(void);

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg);

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg);

#endif