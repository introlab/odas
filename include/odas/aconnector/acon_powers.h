#ifndef __ODAS_ACONNECTOR_POWERS
#define __ODAS_ACONNECTOR_POWERS

    /**
    * \file     acon_powers.h
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

    #include "../connector/con_powers.h"
    #include "../amessage/amsg_powers.h"
    #include "../message/msg_powers.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_powers_obj {

        amsg_powers_obj * in;
        amsg_powers_obj ** outs;
        con_powers_obj * con_powers;
        thread_obj * thread;

    } acon_powers_obj;

    acon_powers_obj * acon_powers_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_powers_cfg * msg_powers_config);

    void acon_powers_destroy(acon_powers_obj * obj);

    void * acon_powers_thread(void * ptr);

#endif