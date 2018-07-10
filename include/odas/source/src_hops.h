#ifndef __ODAS_SOURCE_HOPS
#define __ODAS_SOURCE_HOPS

    /**
    * \file     src_hops.h
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
    #include "../signal/hop.h"
    #include "../utils/pcm.h"
    #include "../utils/interleave.h"

    typedef struct src_hops_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;

        int server_id;
        int connection_id;
        unsigned int port;        

        unsigned int nBytes;
        unsigned int bufferSize;
        char * bufferInterleave;
        char * bufferPerChannel;

        msg_hops_obj * out;

    } src_hops_obj;

    typedef struct src_hops_cfg {

        unsigned int port;

    } src_hops_cfg;

    src_hops_obj * src_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config);

    void src_hops_destroy(src_hops_obj * obj);

    void src_hops_connect(src_hops_obj * obj, msg_hops_obj * out);

    void src_hops_disconnect(src_hops_obj * obj);

    void src_hops_open(src_hops_obj * obj);

    void src_hops_close(src_hops_obj * obj);

    int src_hops_process(src_hops_obj * obj);

    int src_hops_process_interface(src_hops_obj * obj);

    void src_hops_process_format(src_hops_obj * obj);

    src_hops_cfg * src_hops_cfg_construct(void);

    void src_hops_cfg_destroy(src_hops_cfg * cfg);

    void src_hops_cfg_printf(const src_hops_cfg * cfg);

#endif