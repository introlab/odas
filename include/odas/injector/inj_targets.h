#ifndef __ODAS_INJECTOR_TARGETS
#define __ODAS_INJECTOR_TARGETS

   /**
    * \file     inj_targets.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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