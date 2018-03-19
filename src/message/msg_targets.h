#ifndef __ODAS_MESSAGE_TARGETS
#define __ODAS_MESSAGE_TARGETS

   /**
    * \file     msg_targets.h
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