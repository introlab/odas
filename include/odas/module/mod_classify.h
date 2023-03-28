#ifndef __ODAS_MODULE_CLASSIFY
#define __ODAS_MODULE_CLASSIFY

   /**
    * \file     mod_classify.h
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
