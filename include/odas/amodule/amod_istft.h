#ifndef __ODAS_AMODULE_ISTFT
#define __ODAS_AMODULE_ISTFT

    /**
    * \file     amod_istft.h
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

    #include "../module/mod_istft.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_istft_obj {

        mod_istft_obj * mod_istft;
        amsg_spectra_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;    

    } amod_istft_obj;

    amod_istft_obj * amod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config);

    void amod_istft_destroy(amod_istft_obj * obj);

    void amod_istft_connect(amod_istft_obj * obj, amsg_spectra_obj * in, amsg_hops_obj * out);

    void amod_istft_disconnect(amod_istft_obj * obj);

    void amod_istft_enable(amod_istft_obj * obj);

    void amod_istft_disable(amod_istft_obj * obj);

    void * amod_istft_thread(void * ptr);    

#endif