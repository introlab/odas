#ifndef __ODAS_SINK_TARGETS
#define __ODAS_SINK_TARGETS

    /**
    * \file     snk_targets.h
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

    #include "../message/msg_targets.h"

    typedef struct snk_targets_obj {

        unsigned long long timeStamp;

        unsigned int nTargets;

        char * buffer;
        unsigned int bufferSize;

        int server_id;
        int connection_id;     
        unsigned int port;       
        
        msg_targets_obj * in;

    } snk_targets_obj;

    typedef struct snk_targets_cfg {

        unsigned int port;

    } snk_targets_cfg;

    snk_targets_obj * snk_targets_construct(const snk_targets_cfg * snk_targets_config, const msg_targets_cfg * msg_targets_config);

    void snk_targets_destroy(snk_targets_obj * obj);

    void snk_targets_connect(snk_targets_obj * obj, msg_targets_obj * in);

    void snk_targets_disconnect(snk_targets_obj * obj);

    void snk_targets_open(snk_targets_obj * obj);

    void snk_targets_close(snk_targets_obj * obj);

    int snk_targets_process(snk_targets_obj * obj);

    void snk_targets_process_interface(snk_targets_obj * obj);

    void snk_targets_process_format(snk_targets_obj * obj);

    snk_targets_cfg * snk_targets_cfg_construct(void);

    void snk_targets_cfg_destroy(snk_targets_cfg * snk_targets_config);

#endif