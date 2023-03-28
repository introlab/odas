#ifndef __ODAS_ASINK_POWERS
#define __ODAS_ASINK_POWERS

    /**
    * \file     asink_powers.h
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

    #include "../amessage/amsg_powers.h"
    #include "../sink/snk_powers.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_powers_obj {

        snk_powers_obj * snk_powers;
        amsg_powers_obj * in;
        thread_obj * thread;

    } asnk_powers_obj;

    asnk_powers_obj * asnk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config);

    void asnk_powers_destroy(asnk_powers_obj * obj);

    void asnk_powers_connect(asnk_powers_obj * obj, amsg_powers_obj * in);

    void asnk_powers_disconnect(asnk_powers_obj * obj);

    void * asnk_powers_thread(void * ptr);

#endif