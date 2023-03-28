#ifndef __ODAS_ACONNECTOR_TARGETS
#define __ODAS_ACONNECTOR_TARGETS

    /**
    * \file     acon_targets.h
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

    #include "../connector/con_targets.h"
    #include "../amessage/amsg_targets.h"
    #include "../message/msg_targets.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_targets_obj {

        amsg_targets_obj * in;
        amsg_targets_obj ** outs;
        con_targets_obj * con_targets;
        thread_obj * thread;

    } acon_targets_obj;

    acon_targets_obj * acon_targets_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_targets_cfg * msg_targets_config);

    void acon_targets_destroy(acon_targets_obj * obj);

    void * acon_targets_thread(void * ptr);

#endif