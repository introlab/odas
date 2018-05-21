#ifndef __ODAS_MODULE_RS
#define __ODAS_MODULE_RS

   /**
    * \file     mod_rs.h
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


    #include "../message/msg_hops.h"

    #include "../signal/hop.h"
    #include "../signal/frame.h"
    #include "../signal/freq.h"

    #include "../system/hop2frame.h"
    #include "../system/hop2hop.h"
    #include "../system/frame2freq.h"
    #include "../system/freq2freq.h"
    #include "../system/freq2frame.h"
    #include "../system/frame2hop.h"

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    typedef struct mod_resample_obj {

        unsigned long long timeStamp;
        char noMorePush;

        char type;

        unsigned int nChannels;
        unsigned int fSin;
        unsigned int fSout;
        unsigned int hopSizeIn;
        unsigned int hopSizeOut;
        float ratio;
        
        unsigned int frameSize;
        unsigned int halfFrameSize;
        unsigned int lowPassCut;

        hop2hop_buffer_obj * hop2hop;

        hop2frame_obj * hop2frame;
        frames_obj * framesAnalysis; 
        frame2freq_obj * frame2freq;
        freqs_obj * freqsAnalysis;
        freq2freq_lowpass_obj * freq2freq_lowpass;
        freqs_obj * freqsSynthesis;
        freq2frame_obj * freq2frame;
        frames_obj * framesSynthesis;
        frame2hop_obj * frame2hop;
        hops_obj * hops;

        msg_hops_obj * in;
        msg_hops_obj * out;

        char enabled;

    } mod_resample_obj;

    typedef struct mod_resample_cfg {
        
        unsigned int fSin;
        unsigned int fSout;

    } mod_resample_cfg;

    mod_resample_obj * mod_resample_construct(const mod_resample_cfg * mod_resample_config, const msg_hops_cfg * msg_hops_in_config, const msg_hops_cfg * msg_hops_out_config);

    void mod_resample_destroy(mod_resample_obj * obj);

    int mod_resample_process_push(mod_resample_obj * obj);

    int mod_resample_process_pop(mod_resample_obj * obj);

    int mod_resample_process_push_down(mod_resample_obj * obj);

    int mod_resample_process_push_up(mod_resample_obj * obj);

    int mod_resample_process_push_same(mod_resample_obj * obj);    

    int mod_resample_process_pop_down(mod_resample_obj * obj);

    int mod_resample_process_pop_up(mod_resample_obj * obj);

    int mod_resample_process_pop_same(mod_resample_obj * obj);    

    void mod_resample_connect(mod_resample_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_resample_disconnect(mod_resample_obj * obj);

    void mod_resample_enable(mod_resample_obj * obj);

    void mod_resample_disable(mod_resample_obj * obj);

    mod_resample_cfg * mod_resample_cfg_construct(void);

    void mod_resample_cfg_destroy(mod_resample_cfg * cfg);

    void mod_resample_cfg_printf(const mod_resample_cfg * cfg);

#endif