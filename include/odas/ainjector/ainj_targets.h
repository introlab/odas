#ifndef __ODAS_AINJECTOR_TARGETS
#define __ODAS_AINJECTOR_TARGETS

    /**
    * \file     ainj_targets.h
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

    #include "../injector/inj_targets.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_targets.h"
    #include "../general/thread.h"

    typedef struct ainj_targets_obj {

        inj_targets_obj * inj_targets;
        amsg_hops_obj * in;
        amsg_targets_obj * out;
        thread_obj * thread;    

    } ainj_targets_obj;

    ainj_targets_obj * ainj_targets_construct(const inj_targets_cfg * inj_targets_config, const msg_hops_cfg * msg_hops_config, const msg_targets_cfg * msg_targets_config);

    void ainj_targets_destroy(ainj_targets_obj * obj);

    void ainj_targets_connect(ainj_targets_obj * obj, amsg_hops_obj * in, amsg_targets_obj * out);

    void ainj_targets_disconnect(ainj_targets_obj * obj);

    void * ainj_targets_thread(void * ptr); 

#endif