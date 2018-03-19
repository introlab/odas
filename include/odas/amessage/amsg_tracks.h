#ifndef __ODAS_AMESSAGE_TRACKS
#define __ODAS_AMESSAGE_TRACKS

    /**
    * \file     amsg_tracks.h
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

    #include "../message/msg_tracks.h"
    #include "../utils/fifo.h"

    typedef struct amsg_tracks_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_tracks_obj;

    amsg_tracks_obj * amsg_tracks_construct(const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config);

    void amsg_tracks_destroy(amsg_tracks_obj * obj);

    msg_tracks_obj * amsg_tracks_filled_pop(amsg_tracks_obj * obj);

    void amsg_tracks_filled_push(amsg_tracks_obj * obj, msg_tracks_obj * msg_tracks);

    msg_tracks_obj * amsg_tracks_empty_pop(amsg_tracks_obj * obj);

    void amsg_tracks_empty_push(amsg_tracks_obj * obj, msg_tracks_obj * msg_tracks);

#endif