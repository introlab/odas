#ifndef __ODAS_SINK_HOPS
#define __ODAS_SINK_HOPS

   /**
    * \file     snk_hops.h
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