#ifndef __ODAS_AMODULE_NOISE
#define __ODAS_AMODULE_NOISE

    /**
    * \file     amod_noise.h
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

    #include "../module/mod_noise.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_powers.h"
    #include "../general/thread.h"

    typedef struct amod_noise_obj {

        mod_noise_obj * mod_noise;
        amsg_spectra_obj * in;
        amsg_powers_obj * out;
        thread_obj * thread;    

    } amod_noise_obj;

    amod_noise_obj * amod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config);

    void amod_noise_destroy(amod_noise_obj * obj);

    void amod_noise_connect(amod_noise_obj * obj, amsg_spectra_obj * in, amsg_powers_obj * out);

    void amod_noise_disconnect(amod_noise_obj * obj);

    void amod_noise_enable(amod_noise_obj * obj);

    void amod_noise_disable(amod_noise_obj * obj);

    void * amod_noise_thread(void * ptr);    

#endif