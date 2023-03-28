#ifndef __ODAS_AMODULE_STFT
#define __ODAS_AMODULE_STFT

    /**
    * \file     amod_stft.h
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

    #include "../module/mod_stft.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_stft_obj {

        mod_stft_obj * mod_stft;
        amsg_hops_obj * in;
        amsg_spectra_obj * out;
        thread_obj * thread;    

    } amod_stft_obj;

    amod_stft_obj * amod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config);

    void amod_stft_destroy(amod_stft_obj * obj);

    void amod_stft_connect(amod_stft_obj * obj, amsg_hops_obj * in, amsg_spectra_obj * out);

    void amod_stft_disconnect(amod_stft_obj * obj);

    void amod_stft_enable(amod_stft_obj * obj);

    void amod_stft_disable(amod_stft_obj * obj);

    void * amod_stft_thread(void * ptr);    

#endif