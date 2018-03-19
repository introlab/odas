#ifndef __ODAS_SINK_HOPS
#define __ODAS_SINK_HOPS

   /**
    * \file     snk_hops.h
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
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    typedef struct snk_hops_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        char * buffer;
        unsigned int bufferSize;

        FILE * fp;

        struct sockaddr_in sserver;
        int sid;

        char bytes[4];

        msg_hops_obj * in;

    } snk_hops_obj;

    typedef struct snk_hops_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_hops_cfg;

    snk_hops_obj * snk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config);

    void snk_hops_destroy(snk_hops_obj * obj);

    void snk_hops_connect(snk_hops_obj * obj, msg_hops_obj * in);

    void snk_hops_disconnect(snk_hops_obj * obj);

    void snk_hops_open(snk_hops_obj * obj);

    void snk_hops_open_interface_blackhole(snk_hops_obj * obj);

    void snk_hops_open_interface_file(snk_hops_obj * obj);

    void snk_hops_open_interface_socket(snk_hops_obj * obj);

    void snk_hops_close(snk_hops_obj * obj);

    void snk_hops_close_interface_blackhole(snk_hops_obj * obj);

    void snk_hops_close_interface_file(snk_hops_obj * obj);

    void snk_hops_close_interface_socket(snk_hops_obj * obj);

    int snk_hops_process(snk_hops_obj * obj);

    void snk_hops_process_interface_blackhole(snk_hops_obj * obj);

    void snk_hops_process_interface_file(snk_hops_obj * obj);

    void snk_hops_process_interface_socket(snk_hops_obj * obj);

    void snk_hops_process_format_binary_int08(snk_hops_obj * obj);

    void snk_hops_process_format_binary_int16(snk_hops_obj * obj);

    void snk_hops_process_format_binary_int24(snk_hops_obj * obj);

    void snk_hops_process_format_binary_int32(snk_hops_obj * obj);

    void snk_hops_process_format_undefined(snk_hops_obj * obj);

    snk_hops_cfg * snk_hops_cfg_construct(void);

    void snk_hops_cfg_destroy(snk_hops_cfg * snk_hops_config);

#endif