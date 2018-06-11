#ifndef __ODAS_MODULE_BF
#define __ODAS_MODULE_BF

   /**
    * \file     mod_bf.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-30
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

    typedef struct mod_bf_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        char mode;

        beampatterns_obj * ds_beampatterns_mics;
        steers_obj * ds_steers;
        gains_obj * ds_gains;
        masks_obj * ds_masks;
        track2gain_obj * ds_track2gain;
        gain2mask_obj * ds_gain2mask;
        track2steer_obj * ds_track2steer;
        steer2demixing_ds_obj * ds_steer2demixing;
        demixings_obj * ds_demixings;
        demixing2freq_obj * ds_demixing2freq;

        msg_spectra_obj * in1;
        msg_tracks_obj * in2;
        msg_spectra_obj * out;

        char enabled;

    } mod_bf_obj;

    typedef struct mod_bf_cfg {

        char mode;

        unsigned int nThetas;
        float gainMin;

        float epsilon;

        mics_obj * mics;
        samplerate_obj * samplerate;
        soundspeed_obj * soundspeed;

    } mod_bf_cfg;

    mod_bf_obj * mod_bf_construct(const mod_bf_cfg * mod_bf_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_bf_destroy(mod_bf_obj * obj);

    int mod_bf_process(mod_bf_obj * obj);

    int mod_bf_process_dds(mod_bf_obj * obj);

    void mod_bf_connect(mod_bf_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out);

    void mod_bf_disconnect(mod_bf_obj * obj);

    void mod_bf_enable(mod_bf_obj * obj);

    void mod_bf_disable(mod_bf_obj * obj);

    mod_bf_cfg * mod_bf_cfg_construct(void);

    void mod_bf_cfg_destroy(mod_bf_cfg * cfg);

    void mod_bf_cfg_printf(const mod_bf_cfg * cfg);

#endif