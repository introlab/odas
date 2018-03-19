#ifndef __ODAS_MESSAGE_HOPS
#define __ODAS_MESSAGE_HOPS

   /**
    * \file     msg_hops.h
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