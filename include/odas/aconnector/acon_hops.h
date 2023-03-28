#ifndef __ODAS_ACONNECTOR_HOPS
#define __ODAS_ACONNECTOR_HOPS

    /**
    * \file     acon_hops.h
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

    #include "../connector/con_hops.h"
    #include "../amessage/amsg_hops.h"
    #include "../message/msg_hops.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_hops_obj {

        amsg_hops_obj * in;
        amsg_hops_obj ** outs;
        con_hops_obj * con_hops;
        thread_obj * thread;

    } acon_hops_obj;

    acon_hops_obj * acon_hops_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_hops_cfg * msg_hops_config);

    void acon_hops_destroy(acon_hops_obj * obj);

    void * acon_hops_thread(void * ptr);

#endif