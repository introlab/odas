#ifndef __ODAS_MESSAGE_POWERS
#define __ODAS_MESSAGE_POWERS

   /**
    * \file     msg_powers.h
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