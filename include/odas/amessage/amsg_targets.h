#ifndef __ODAS_AMESSAGE_TARGETS
#define __ODAS_AMESSAGE_TARGETS

    /**
    * \file     amsg_targets.h
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

    #include "../message/msg_targets.h"
    #include "../utils/fifo.h"

    typedef struct amsg_targets_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_targets_obj;

    amsg_targets_obj * amsg_targets_construct(const unsigned int nMessages, const msg_targets_cfg * msg_targets_config);

    void amsg_targets_destroy(amsg_targets_obj * obj);

    msg_targets_obj * amsg_targets_filled_pop(amsg_targets_obj * obj);

    void amsg_targets_filled_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets);

    msg_targets_obj * amsg_targets_empty_pop(amsg_targets_obj * obj);

    void amsg_targets_empty_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets);

#endif