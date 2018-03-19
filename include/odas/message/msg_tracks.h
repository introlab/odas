#ifndef __ODAS_MESSAGE_TRACKS
#define __ODAS_MESSAGE_TRACKS

   /**
    * \file     msg_tracks.h
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
    #include "../signal/track.h"

    typedef struct msg_tracks_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        tracks_obj * tracks;

    } msg_tracks_obj;

    typedef struct msg_tracks_cfg {

        unsigned int nTracks;
        unsigned int fS;

    } msg_tracks_cfg;

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg);

    void msg_tracks_destroy(msg_tracks_obj * obj);

    void msg_tracks_copy(msg_tracks_obj * dest, const msg_tracks_obj * src);

    void msg_tracks_zero(msg_tracks_obj * obj);

    unsigned int msg_tracks_isZero(const msg_tracks_obj * obj);

    msg_tracks_cfg * msg_tracks_cfg_construct(void);

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg);

    void msg_tracks_cfg_printf(const msg_tracks_cfg * msg_tracks_config);

#endif