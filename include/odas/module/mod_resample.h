#ifndef __ODAS_MODULE_RS
#define __ODAS_MODULE_RS

   /**
    * \file     mod_rs.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
        double ratio;

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
