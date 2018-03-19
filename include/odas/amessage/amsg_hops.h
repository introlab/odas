#ifndef __ODAS_AMESSAGE_HOPS
#define __ODAS_AMESSAGE_HOPS

    /**
    * \file     amsg_hops.h
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

    #include "../message/msg_hops.h"
    #include "../utils/fifo.h"

    typedef struct amsg_hops_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_hops_obj;

    amsg_hops_obj * amsg_hops_construct(const unsigned int nMessages, const msg_hops_cfg * msg_hops_config);

    void amsg_hops_destroy(amsg_hops_obj * obj);

    msg_hops_obj * amsg_hops_filled_pop(amsg_hops_obj * obj);

    void amsg_hops_filled_push(amsg_hops_obj * obj, msg_hops_obj * msg_hops);

    msg_hops_obj * amsg_hops_empty_pop(amsg_hops_obj * obj);

    void amsg_hops_empty_push(amsg_hops_obj * obj, msg_hops_obj * msg_hops);

#endif