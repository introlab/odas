#ifndef __ODAS_ACONNECTOR_TRACKS
#define __ODAS_ACONNECTOR_TRACKS

    /**
    * \file     acon_tracks.h
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

    #include "../connector/con_tracks.h"
    #include "../amessage/amsg_tracks.h"
    #include "../message/msg_tracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_tracks_obj {

        amsg_tracks_obj * in;
        amsg_tracks_obj ** outs;
        con_tracks_obj * con_tracks;
        thread_obj * thread;

    } acon_tracks_obj;

    acon_tracks_obj * acon_tracks_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config);

    void acon_tracks_destroy(acon_tracks_obj * obj);

    void * acon_tracks_thread(void * ptr);

#endif