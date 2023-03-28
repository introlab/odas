#ifndef __ODAS_SINK_POTS
#define __ODAS_SINK_POTS

   /**
    * \file     snk_pots.h
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