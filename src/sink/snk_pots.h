#ifndef __ODAS_SINK_POTS
#define __ODAS_SINK_POTS

   /**
    * \file     snk_pots.h
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
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_pots.h"

    typedef struct snk_pots_obj {

        unsigned long long timeStamp;

        unsigned int nPots;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        char * buffer;
        unsigned int bufferSize;

        FILE * fp;

        struct sockaddr_in sserver;
        int sid;

        msg_pots_obj * in;

    } snk_pots_obj;

    typedef struct snk_pots_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_pots_cfg;

    snk_pots_obj * snk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config);

    void snk_pots_destroy(snk_pots_obj * obj);

    void snk_pots_connect(snk_pots_obj * obj, msg_pots_obj * in);

    void snk_pots_disconnect(snk_pots_obj * obj);

    void snk_pots_open(snk_pots_obj * obj);

    void snk_pots_open_interface_blackhole(snk_pots_obj * obj);

    void snk_pots_open_interface_file(snk_pots_obj * obj);

    void snk_pots_open_interface_socket(snk_pots_obj * obj);

    void snk_pots_open_interface_terminal(snk_pots_obj * obj);

    void snk_pots_close(snk_pots_obj * obj);

    void snk_pots_close_interface_blackhole(snk_pots_obj * obj);

    void snk_pots_close_interface_file(snk_pots_obj * obj);

    void snk_pots_close_interface_socket(snk_pots_obj * obj);

    void snk_pots_close_interface_terminal(snk_pots_obj * obj);

    int snk_pots_process(snk_pots_obj * obj);

    void snk_pots_process_interface_blackhole(snk_pots_obj * obj);

    void snk_pots_process_interface_file(snk_pots_obj * obj);

    void snk_pots_process_interface_socket(snk_pots_obj * obj);

    void snk_pots_process_interface_terminal(snk_pots_obj * obj);

    void snk_pots_process_format_binary_float(snk_pots_obj * obj);

    void snk_pots_process_format_text_json(snk_pots_obj * obj);

    void snk_pots_process_format_undefined(snk_pots_obj * obj);

    snk_pots_cfg * snk_pots_cfg_construct(void);

    void snk_pots_cfg_destroy(snk_pots_cfg * snk_pots_config);

#endif