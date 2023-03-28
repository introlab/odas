#ifndef __ODAS_MESSAGE_HOPS
#define __ODAS_MESSAGE_HOPS

   /**
    * \file     msg_hops.h
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

    #include <stdlib.h>
    #include "../signal/hop.h"
    #include "../utils/fifo.h"

    typedef struct msg_hops_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        hops_obj * hops;

    } msg_hops_obj;

    typedef struct msg_hops_cfg {

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_hops_cfg;

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * msg_hops_config);

    void msg_hops_destroy(msg_hops_obj * obj);

    void msg_hops_copy(msg_hops_obj * dest, const msg_hops_obj * src);

    void msg_hops_zero(msg_hops_obj * obj);

    unsigned int msg_hops_isZero(const msg_hops_obj * obj);

    msg_hops_cfg * msg_hops_cfg_construct(void);

    void msg_hops_cfg_destroy(msg_hops_cfg * msg_hops_config);

    void msg_hops_cfg_printf(const msg_hops_cfg * msg_hops_config);

#endif