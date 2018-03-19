#ifndef __ODAS_AMESSAGE_POWERS
#define __ODAS_AMESSAGE_POWERS

    /**
    * \file     amsg_powers.h
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

    #include "../message/msg_powers.h"
    #include "../utils/fifo.h"

    typedef struct amsg_powers_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_powers_obj;

    amsg_powers_obj * amsg_powers_construct(const unsigned int nMessages, const msg_powers_cfg * msg_powers_config);

    void amsg_powers_destroy(amsg_powers_obj * obj);

    msg_powers_obj * amsg_powers_filled_pop(amsg_powers_obj * obj);

    void amsg_powers_filled_push(amsg_powers_obj * obj, msg_powers_obj * msg_powers);

    msg_powers_obj * amsg_powers_empty_pop(amsg_powers_obj * obj);

    void amsg_powers_empty_push(amsg_powers_obj * obj, msg_powers_obj * msg_powers);

#endif