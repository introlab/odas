#ifndef __ODAS_MODULE_CLASSIFY
#define __ODAS_MODULE_CLASSIFY

   /**
    * \file     mod_classify.h
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
    #include <stdio.h>

    #include <message/msg_hops.h>
    #include <message/msg_tracks.h>
    #include <message/msg_categories.h>

    #include <signal/acorr.h>
    #include <signal/category.h>
    #include <signal/frame.h>
    #include <signal/freq.h>
    #include <signal/hop.h>
    #include <signal/pitch.h>
    
    #include <system/acorr2pitch.h>
    #include <system/frame2freq.h>
    #include <system/freq2acorr.h>
    #include <system/hop2frame.h>
    #include <system/pitch2category.h>

    typedef struct mod_classify_obj {

        frames_obj * frames;
        freqs_obj * freqs;
        acorrs_obj * acorrs;
        pitches_obj * pitches;

        hop2frame_obj * hop2frame;
        frame2freq_obj * frame2freq;
        freq2acorr_obj * freq2acorr;
        acorr2pitch_obj * acorr2pitch;
        pitch2category_obj * pitch2category;

        msg_hops_obj * in1;
        msg_tracks_obj * in2;
        msg_categories_obj * out;

        char enabled;

    } mod_classify_obj;

    typedef struct mod_classify_cfg {

        unsigned int frameSize;
        unsigned int winSize;

        float tauMin;
        float tauMax;
        float deltaTauMax;
        float alpha;
        float gamma;
        float phiMin;
        float r0;        

    } mod_classify_cfg;

    mod_classify_obj * mod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config, const msg_categories_cfg * msg_categories_config);

    void mod_classify_destroy(mod_classify_obj * obj);

    int mod_classify_process(mod_classify_obj * obj);

    void mod_classify_connect(mod_classify_obj * obj, msg_hops_obj * in1, msg_tracks_obj * in2, msg_categories_obj * out);

    void mod_classify_disconnect(mod_classify_obj * obj);

    void mod_classify_enable(mod_classify_obj * obj);

    void mod_classify_disable(mod_classify_obj * obj);

    mod_classify_cfg * mod_classify_cfg_construct(void);

    void mod_classify_cfg_destroy(mod_classify_cfg * cfg);

    void mod_classify_cfg_printf(const mod_classify_cfg * cfg);

#endif
