#ifndef __ODAS_SINK_HOPSTRACKS
#define __ODAS_SINK_HOPSTRACKS

    /**
    * \file     snk_hopstracks.h
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
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include "../message/msg_hops.h"
    #include "../message/msg_tracks.h"
    #include "../utils/interleave.h"
    #include "../utils/pcm.h"

    typedef struct snk_hopstracks_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;

        unsigned int nBytes;
        unsigned int bufferSize;
        char * bufferInterleave;
        char * bufferPerChannel;

        int server_id;
        int connection_id;
        unsigned int port;       

        msg_hops_obj * in1;
        msg_tracks_obj * in2;

    } snk_hopstracks_obj;

    typedef struct snk_hopstracks_cfg {

        unsigned int port;

    } snk_hopstracks_cfg;

    snk_hopstracks_obj * snk_hopstracks_construct(const snk_hopstracks_cfg * snk_hopstracks_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config);

    void snk_hopstracks_destroy(snk_hopstracks_obj * obj);

    void snk_hopstracks_connect(snk_hopstracks_obj * obj, msg_hops_obj * in1, msg_tracks_obj * in2);

    void snk_hopstracks_disconnect(snk_hopstracks_obj * obj);

    void snk_hopstracks_open(snk_hopstracks_obj * obj);

    void snk_hopstracks_close(snk_hopstracks_obj * obj);

    int snk_hopstracks_process(snk_hopstracks_obj * obj);

    void snk_hopstracks_process_interface(snk_hopstracks_obj * obj);

    void snk_hopstracks_process_format(snk_hopstracks_obj * obj);

    snk_hopstracks_cfg * snk_hopstracks_cfg_construct(void);

    void snk_hopstracks_cfg_destroy(snk_hopstracks_cfg * snk_hopstracks_config);

#endif