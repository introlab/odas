#ifndef __ODAS_SERIALIZER_TRACKS
#define __ODAS_SERIALIZER_TRACKS

   /**
    * \file     ser_tracks.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-08
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

    #include "../message/msg_tracks.h"  

    typedef struct ser_tracks_obj {

        unsigned long long timeStamp;

        unsigned int nTracks;
        unsigned int fS;

        char * string;

        msg_tracks_obj * in;
        char * out;

    } ser_tracks_obj;

    typedef struct ser_tracks_cfg {

    } ser_tracks_cfg;

    ser_tracks_obj * ser_tracks_construct(const ser_tracks_cfg * ser_tracks_config, const msg_tracks_cfg * msg_tracks_config);

    void ser_tracks_destroy(ser_tracks_obj * obj);

    void ser_tracks_connect(ser_tracks_obj * obj, msg_tracks_obj * in, char * out);

    void ser_tracks_disconnect(ser_tracks_obj * obj);

    void ser_tracks_process(ser_tracks_obj * obj);

    ser_tracks_cfg * ser_tracks_cfg_construct(void);

    void ser_tracks_cfg_destroy(ser_tracks_cfg * cfg);

#endif