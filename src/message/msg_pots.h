#ifndef __ODAS_MESSAGE_POTS
#define __ODAS_MESSAGE_POTS

   /**
    * \file     msg_pots.h
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
    #include "../signal/pot.h"

    typedef struct msg_pots_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        pots_obj * pots;

    } msg_pots_obj;

    typedef struct msg_pots_cfg {

        unsigned int nPots;
        unsigned int fS;

    } msg_pots_cfg;

    msg_pots_obj * msg_pots_construct(const msg_pots_cfg * cfg);

    void msg_pots_destroy(msg_pots_obj * obj);

    void msg_pots_copy(msg_pots_obj * dest, const msg_pots_obj * src);

    void msg_pots_zero(msg_pots_obj * obj);

    unsigned int msg_pots_isZero(const msg_pots_obj * obj);

    msg_pots_cfg * msg_pots_cfg_construct(void);

    void msg_pots_cfg_destroy(msg_pots_cfg * cfg);

    void msg_pots_cfg_printf(const msg_pots_cfg * msg_pots_config);

#endif