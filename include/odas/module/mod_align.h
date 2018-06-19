#ifndef __ODAS_MODULE_ALIGN
#define __ODAS_MODULE_ALIGN

   /**
    * \file     mod_align.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.1
    * \date     2018-06-14
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
  
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>

    #include "../message/msg_hops.h"
    #include "../message/msg_targets.h"

    typedef struct mod_align_obj {

        unsigned long long timeStamp;

        msg_targets_obj * in1;
        msg_hops_obj * in2;
        msg_targets_obj * out;

        unsigned int fSin;
        unsigned int fSout;

        targets_obj * targets;

        char enabled;

    } mod_align_obj;

    typedef struct mod_align_cfg {

    } mod_align_cfg;

    mod_align_obj * mod_align_construct(const mod_align_cfg * mod_align_config, const msg_targets_cfg * msg_targets_in_config, const msg_hops_cfg * msg_hops_in_config, const msg_targets_cfg * msg_targets_out_config);

    void mod_align_destroy(mod_align_obj * obj);

    int mod_align_process_push(mod_align_obj * obj);

    int mod_align_process_pop(mod_align_obj * obj);

    void mod_align_connect(mod_align_obj * obj, msg_targets_obj * in1, msg_hops_obj * in2, msg_targets_obj * out);

    void mod_align_disconnect(mod_align_obj * obj);

    void mod_align_enable(mod_align_obj * obj);

    void mod_align_disable(mod_align_obj * obj);

    mod_align_cfg * mod_align_cfg_construct(void);

    void mod_align_cfg_destroy(mod_align_cfg * cfg);

    void mod_align_cfg_printf(const mod_align_cfg * cfg);

#endif