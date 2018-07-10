#ifndef __ODAS_SINK_TRACKS
#define __ODAS_SINK_TRACKS

    /**
    * \file     snk_tracks.h
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #include "../message/msg_tracks.h"

    typedef struct snk_tracks_obj {

        unsigned long long timeStamp;

        unsigned int nTracks;

        char * buffer;
        unsigned int bufferSize;

        int server_id;
        int connection_id;     
        unsigned int port;       
        
        msg_tracks_obj * in;

    } snk_tracks_obj;

    typedef struct snk_tracks_cfg {

        unsigned int port;

    } snk_tracks_cfg;

    snk_tracks_obj * snk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config);

    void snk_tracks_destroy(snk_tracks_obj * obj);

    void snk_tracks_connect(snk_tracks_obj * obj, msg_tracks_obj * in);

    void snk_tracks_disconnect(snk_tracks_obj * obj);

    void snk_tracks_open(snk_tracks_obj * obj);

    void snk_tracks_close(snk_tracks_obj * obj);

    int snk_tracks_process(snk_tracks_obj * obj);

    void snk_tracks_process_interface(snk_tracks_obj * obj);

    void snk_tracks_process_format(snk_tracks_obj * obj);

    snk_tracks_cfg * snk_tracks_cfg_construct(void);

    void snk_tracks_cfg_destroy(snk_tracks_cfg * snk_tracks_config);

#endif