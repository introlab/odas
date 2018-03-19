#ifndef __ODAS_ASINK_TRACKS
#define __ODAS_ASINK_TRACKS

    /**
    * \file     asink_tracks.h
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

    #include "../amessage/amsg_tracks.h"
    #include "../sink/snk_tracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_tracks_obj {

        snk_tracks_obj * snk_tracks;
        amsg_tracks_obj * in;
        thread_obj * thread;

    } asnk_tracks_obj;

    asnk_tracks_obj * asnk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config);

    void asnk_tracks_destroy(asnk_tracks_obj * obj);

    void asnk_tracks_connect(asnk_tracks_obj * obj, amsg_tracks_obj * in);

    void asnk_tracks_disconnect(asnk_tracks_obj * obj);

    void * asnk_tracks_thread(void * ptr);

#endif