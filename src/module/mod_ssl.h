#ifndef __ODAS_MODULE_SSL
#define __ODAS_MODULE_SSL

    #include <stdlib.h>
    #include <string.h>

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"

    #include "../signal/aimg.h"   
    #include "../signal/freq.h"
    #include "../signal/xcorr.h"
    
    #include "../system/freq2freq.h"
    #include "../system/freq2xcorr.h"
    #include "../system/xcorr2aimg.h"
    #include "../system/xcorr2xcorr.h"

    #include "../init/scanning.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_pots.h"


    typedef struct mod_ssl_obj {

        unsigned int nChannels;
        unsigned int nPairs;
        unsigned int nPots;
        unsigned int nLevels;
        unsigned int frameSize;
        unsigned int halfFrameSize;

        scans_obj * scans;

        freqs_obj * phasors;   
        freqs_obj * products;
        xcorrs_obj * xcorrs;
        xcorrs_obj * xcorrsMax;
        
        freq2freq_obj * freq2freq;
        freq2xcorr_obj * freq2xcorr;
        xcorr2xcorr_obj * xcorr2xcorr;
        
        aimg_obj ** aimgs;
        xcorr2aimg_obj ** xcorr2aimg;

        pots_obj * pots;

        msg_spectra_obj * in;
        msg_pots_obj * out;

    } mod_ssl_obj;

    typedef struct mod_ssl_cfg {

        mics_obj * mics;
        samplerate_obj * samplerate;
        soundspeed_obj * soundspeed;

        float epsilon; 
        unsigned int nLevels;
        unsigned int * levels;
        signed int * deltas;
        unsigned int nMatches;
        float probMin;
        unsigned int nRefinedLevels;
        unsigned int nThetas;
        float gainMin;

    } mod_ssl_cfg;

    mod_ssl_obj * mod_ssl_construct(const mod_ssl_cfg * mod_ssl_config, const msg_spectra_cfg * msg_spectra_config, const msg_pots_cfg * msg_pots_config);

    void mod_ssl_destroy(mod_ssl_obj * obj);

    int mod_ssl_process(mod_ssl_obj * obj);

    void mod_ssl_connect(mod_ssl_obj * obj, msg_spectra_obj * in, msg_pots_obj * out);

    void mod_ssl_disconnect(mod_ssl_obj * obj);

    mod_ssl_cfg * mod_ssl_cfg_construct(void);

    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg);

    void mod_ssl_cfg_printf(const mod_ssl_cfg * cfg);

#endif