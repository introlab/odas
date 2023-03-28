#ifndef __ODAS_MESSAGE_TARGETS
#define __ODAS_MESSAGE_TARGETS

   /**
    * \file     msg_targets.h
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
    #include "../signal/target.h"

    typedef struct msg_targets_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        targets_obj * targets;

    } msg_targets_obj;

    typedef struct msg_targets_cfg {

        unsigned int nTargets;
        unsigned int fS;

    } msg_targets_cfg;

    msg_targets_obj * msg_targets_construct(const msg_targets_cfg * cfg);

    void msg_targets_destroy(msg_targets_obj * obj);

    void msg_targets_copy(msg_targets_obj * dest, const msg_targets_obj * src);

    void msg_targets_zero(msg_targets_obj * obj);

    unsigned int msg_targets_isZero(const msg_targets_obj * obj);

    msg_targets_cfg * msg_targets_cfg_construct(void);

    void msg_targets_cfg_destroy(msg_targets_cfg * cfg);

    void msg_targets_cfg_printf(const msg_targets_cfg * msg_targets_config);

#endif