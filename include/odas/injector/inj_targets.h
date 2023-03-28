#ifndef __ODAS_INJECTOR_TARGETS
#define __ODAS_INJECTOR_TARGETS

   /**
    * \file     inj_targets.h
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

    #include "../message/msg_hops.h"
    #include "../message/msg_targets.h"

    #include "../general/format.h"
    #include "../general/interface.h"

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct inj_targets_obj {

        unsigned long long timeStamp;

        unsigned int nTargets;
        unsigned int fS;

        msg_hops_obj * in;
        msg_targets_obj * out;

        targets_obj * targets;

    } inj_targets_obj;

    typedef struct inj_targets_cfg {

        unsigned int nTargets;
        targets_obj * targets;

    } inj_targets_cfg;

    inj_targets_obj * inj_targets_construct(const inj_targets_cfg * inj_targets_config, const msg_hops_cfg * msg_hops_config, const msg_targets_cfg * msg_targets_config);

    void inj_targets_destroy(inj_targets_obj * obj);

    void inj_targets_connect(inj_targets_obj * obj, msg_hops_obj * in, msg_targets_obj * out);

    void inj_targets_disconnect(inj_targets_obj * obj);
    
    int inj_targets_process(inj_targets_obj * obj);

    inj_targets_cfg * inj_targets_cfg_construct(void);

    void inj_targets_cfg_destroy(inj_targets_cfg * cfg);

    void inj_targets_cfg_printf(const inj_targets_cfg * cfg);

#endif