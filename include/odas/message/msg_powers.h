#ifndef __ODAS_MESSAGE_POWERS
#define __ODAS_MESSAGE_POWERS

   /**
    * \file     msg_powers.h
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

    #include "../signal/env.h"

    typedef struct msg_powers_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        envs_obj * envs;

    } msg_powers_obj;

    typedef struct msg_powers_cfg {

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_powers_cfg;

    msg_powers_obj * msg_powers_construct(const msg_powers_cfg * msg_powers_config);

    void msg_powers_destroy(msg_powers_obj * obj);

    void msg_powers_copy(msg_powers_obj * dest, const msg_powers_obj * src);

    void msg_powers_zero(msg_powers_obj * obj);

    unsigned int msg_powers_isZero(const msg_powers_obj * obj);

    msg_powers_cfg * msg_powers_cfg_construct(void);

    void msg_powers_cfg_destroy(msg_powers_cfg * msg_powers_config);

    void msg_powers_cfg_printf(const msg_powers_cfg * msg_powers_config);

#endif