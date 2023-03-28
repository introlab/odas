#ifndef __ODAS_AMODULE_SST
#define __ODAS_AMODULE_SST

    /**
    * \file     amod_sst.h
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

    #include "../module/mod_ssl.h"
    #include "../module/mod_sst.h"
    #include "../amessage/amsg_pots.h"
    #include "../amessage/amsg_targets.h"
    #include "../amessage/amsg_tracks.h"
    #include "../general/thread.h"

    typedef struct amod_sst_obj {

        mod_sst_obj * mod_sst;
        amsg_pots_obj * in1;
        amsg_targets_obj * in2;
        amsg_tracks_obj * out;
        thread_obj * thread;    

    } amod_sst_obj;

    amod_sst_obj * amod_sst_construct(const mod_sst_cfg * mod_sst_config, const mod_ssl_cfg * mod_ssl_config, const msg_pots_cfg * msg_pots_config, const msg_targets_cfg * msg_targets_config, const msg_tracks_cfg * msg_tracks_config);

    void amod_sst_destroy(amod_sst_obj * obj);

    void amod_sst_connect(amod_sst_obj * obj, amsg_pots_obj * in1, amsg_targets_obj * in2, amsg_tracks_obj * out);

    void amod_sst_disconnect(amod_sst_obj * obj);

    void amod_sst_enable(amod_sst_obj * obj);

    void amod_sst_disable(amod_sst_obj * obj);

    void * amod_sst_thread(void * ptr);    

#endif