#ifndef __ODAS_AMESSAGE_POTS
#define __ODAS_AMESSAGE_POTS

    /**
    * \file     amsg_pots.h
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

    #include "../message/msg_pots.h"
    #include "../utils/fifo.h"

    typedef struct amsg_pots_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_pots_obj;

    amsg_pots_obj * amsg_pots_construct(const unsigned int nMessages, const msg_pots_cfg * msg_pots_config);

    void amsg_pots_destroy(amsg_pots_obj * obj);

    msg_pots_obj * amsg_pots_filled_pop(amsg_pots_obj * obj);

    void amsg_pots_filled_push(amsg_pots_obj * obj, msg_pots_obj * msg_pots);

    msg_pots_obj * amsg_pots_empty_pop(amsg_pots_obj * obj);

    void amsg_pots_empty_push(amsg_pots_obj * obj, msg_pots_obj * msg_pots);

#endif