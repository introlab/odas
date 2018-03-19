#ifndef __ODAS_SINK_CATEGORIES
#define __ODAS_SINK_CATEGORIES

   /**
    * \file     snk_categories.h
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
    #include "../message/msg_categories.h"
    #include "../utils/pcm.h"

    typedef struct snk_categories_obj {

        unsigned long long timeStamp;

        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        char * buffer;
        unsigned int bufferSize;

        FILE * fp;

        struct sockaddr_in sserver;
        int sid;

        msg_categories_obj * in;

    } snk_categories_obj;

    typedef struct snk_categories_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_categories_cfg;

    snk_categories_obj * snk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config);

    void snk_categories_destroy(snk_categories_obj * obj);

    void snk_categories_connect(snk_categories_obj * obj, msg_categories_obj * in);

    void snk_categories_disconnect(snk_categories_obj * obj);

    void snk_categories_open(snk_categories_obj * obj);

    void snk_categories_open_interface_blackhole(snk_categories_obj * obj);

    void snk_categories_open_interface_file(snk_categories_obj * obj);

    void snk_categories_open_interface_socket(snk_categories_obj * obj);

    void snk_categories_open_interface_terminal(snk_categories_obj * obj);

    void snk_categories_close(snk_categories_obj * obj);

    void snk_categories_close_interface_blackhole(snk_categories_obj * obj);

    void snk_categories_close_interface_file(snk_categories_obj * obj);

    void snk_categories_close_interface_socket(snk_categories_obj * obj);

    void snk_categories_close_interface_terminal(snk_categories_obj * obj);

    int snk_categories_process(snk_categories_obj * obj);

    void snk_categories_process_interface_blackhole(snk_categories_obj * obj);

    void snk_categories_process_interface_file(snk_categories_obj * obj);

    void snk_categories_process_interface_socket(snk_categories_obj * obj);

    void snk_categories_process_interface_terminal(snk_categories_obj * obj);

    void snk_categories_process_format_text_json(snk_categories_obj * obj);

    void snk_categories_process_format_undefined(snk_categories_obj * obj);

    snk_categories_cfg * snk_categories_cfg_construct(void);

    void snk_categories_cfg_destroy(snk_categories_cfg * snk_categories_config);

#endif