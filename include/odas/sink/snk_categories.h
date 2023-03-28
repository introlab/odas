#ifndef __ODAS_SINK_CATEGORIES
#define __ODAS_SINK_CATEGORIES

   /**
    * \file     snk_categories.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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