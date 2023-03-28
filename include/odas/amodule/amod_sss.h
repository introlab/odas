#ifndef __ODAS_AMODULE_SSS
#define __ODAS_AMODULE_SSS

    /**
    * \file     amod_sss.h
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

    #include "../module/mod_sss.h"
    #include "../amessage/amsg_powers.h"
    #include "../amessage/amsg_tracks.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_sss_obj {

        mod_sss_obj * mod_sss;
        amsg_spectra_obj * in1;
        amsg_powers_obj * in2;
        amsg_tracks_obj * in3;
        amsg_spectra_obj * out1;
        amsg_spectra_obj * out2;
        thread_obj * thread;    

    } amod_sss_obj;

    amod_sss_obj * amod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config);

    void amod_sss_destroy(amod_sss_obj * obj);

    void amod_sss_connect(amod_sss_obj * obj, amsg_spectra_obj * in1, amsg_powers_obj * in2, amsg_tracks_obj * in3, amsg_spectra_obj * out1, amsg_spectra_obj * out2);

    void amod_sss_disconnect(amod_sss_obj * obj);

    void amod_sss_enable(amod_sss_obj * obj);

    void amod_sss_disable(amod_sss_obj * obj);

    void * amod_sss_thread(void * ptr);        

#endif