#ifndef __ODAS_MODULE_STFT
#define __ODAS_MODULE_STFT

   /**
    * \file     mod_stft.h
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

    #include "../system/hop2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2freq.h"
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    typedef struct mod_stft_obj {

        hop2frame_obj * hop2frame;
        frames_obj * frames;
        frame2freq_obj * frame2freq;

        msg_hops_obj * in;
        msg_spectra_obj * out;        

        char enabled;

    } mod_stft_obj;

    typedef struct mod_stft_cfg {
        
    } mod_stft_cfg;

    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_stft_destroy(mod_stft_obj * obj);

    int mod_stft_process(mod_stft_obj * obj);

    void mod_stft_connect(mod_stft_obj * obj, msg_hops_obj * in, msg_spectra_obj * out);

    void mod_stft_disconnect(mod_stft_obj * obj);

    void mod_stft_enable(mod_stft_obj * obj);

    void mod_stft_disable(mod_stft_obj * obj);

    mod_stft_cfg * mod_stft_cfg_construct(void);

    void mod_stft_cfg_destroy(mod_stft_cfg * cfg);

    void mod_stft_cfg_printf(const mod_stft_cfg * cfg);

#endif