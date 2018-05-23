#ifndef __ODAS_MODULE_SSL
#define __ODAS_MODULE_SSL

   /**
    * \file     mod_ssl.h
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

    #include <stdlib.h>
    #include <string.h>

    #include "../general/mic.h"
    #include "../general/samplerate.h"
    #include "../general/soundspeed.h"
    #include "../general/spatialfilter.h"

    #include "../signal/aimg.h"   
    #include "../signal/env.h"
    #include "../signal/freq.h"
    #include "../signal/xcorr.h"
    
    #include "../system/env2env.h"
    #include "../system/freq2env.h"
    #include "../system/freq2freq.h"
    #include "../system/freq2xcorr.h"
    #include "../system/xcorr2aimg.h"
    #include "../system/xcorr2xcorr.h"

    #include "../init/scanning.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_powers.h"
    #include "../message/msg_pots.h"


    typedef struct mod_ssl_obj {

        unsigned int nChannels;
        unsigned int nPairs;
        unsigned int nPots;
        unsigned int nLevels;
        unsigned int frameSize;
        unsigned int halfFrameSize;
        unsigned int frameSizeInterp;
        unsigned int halfFrameSizeInterp;
        unsigned int interpRate;

        scans_obj * scans;

        freqs_obj * phasors;   
        freqs_obj * products;
        freqs_obj * productsInterp;
        xcorrs_obj * xcorrs;
        xcorrs_obj * xcorrsMax;
       
        freq2env_obj * freq2env;
        freq2freq_phasor_obj * freq2freq_phasor;
        freq2freq_product_obj * freq2freq_product;
        freq2freq_interpolate_obj * freq2freq_interpolate;
        freq2xcorr_obj * freq2xcorr;
        xcorr2xcorr_obj * xcorr2xcorr;
        
        aimg_obj ** aimgs;
        xcorr2aimg_obj ** xcorr2aimg;

        pots_obj * pots;

        msg_spectra_obj * in;
        msg_pots_obj * out;

        char enabled;

    } mod_ssl_obj;

    typedef struct mod_ssl_cfg {

        mics_obj * mics;
        samplerate_obj * samplerate;
        soundspeed_obj * soundspeed;
        spatialfilters_obj * spatialfilters;

        unsigned int interpRate;
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

    void mod_ssl_enable(mod_ssl_obj * obj);

    void mod_ssl_disable(mod_ssl_obj * obj);

    mod_ssl_cfg * mod_ssl_cfg_construct(void);

    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg);

    void mod_ssl_cfg_printf(const mod_ssl_cfg * cfg);

#endif