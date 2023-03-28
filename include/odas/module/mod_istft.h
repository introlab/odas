#ifndef __ODAS_MODULE_ISTFT
#define __ODAS_MODULE_ISTFT

   /**
    * \file     mod_istft.h
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

    #include "../system/freq2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2hop.h"
        
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    typedef struct mod_istft_obj {

        freq2frame_obj * freq2frame;
        frames_obj * frames;
        frame2hop_obj * frame2hop;

        msg_spectra_obj * in;        
        msg_hops_obj * out;

        char enabled;

    } mod_istft_obj;

    typedef struct mod_istft_cfg {
        
    } mod_istft_cfg;

    mod_istft_obj * mod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config);

    void mod_istft_destroy(mod_istft_obj * obj);

    int mod_istft_process(mod_istft_obj * obj);

    void mod_istft_connect(mod_istft_obj * obj, msg_spectra_obj * in, msg_hops_obj * out);

    void mod_istft_disconnect(mod_istft_obj * obj);

    void mod_istft_enable(mod_istft_obj * obj);

    void mod_istft_disable(mod_istft_obj * obj);

    mod_istft_cfg * mod_istft_cfg_construct(void);

    void mod_istft_cfg_destroy(mod_istft_cfg * cfg);

    void mod_istft_cfg_printf(const mod_istft_cfg * cfg);

#endif