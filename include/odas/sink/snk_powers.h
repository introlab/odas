#ifndef __ODAS_SINK_POWERS
#define __ODAS_SINK_POWERS

   /**
    * \file     snk_powers.h
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

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_powers.h"

    typedef struct snk_powers_obj {

        unsigned long long timeStamp;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        char * buffer;
        unsigned int bufferSize;

        FILE * fp;

        msg_powers_obj * in;

    } snk_powers_obj;

    typedef struct snk_powers_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_powers_cfg;

    snk_powers_obj * snk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config);

    void snk_powers_destroy(snk_powers_obj * obj);

    void snk_powers_connect(snk_powers_obj * obj, msg_powers_obj * in);

    void snk_powers_disconnect(snk_powers_obj * obj);

    void snk_powers_open(snk_powers_obj * obj);

    void snk_powers_open_interface_blackhole(snk_powers_obj * obj);

    void snk_powers_close(snk_powers_obj * obj);

    void snk_powers_close_interface_blackhole(snk_powers_obj * obj);

    int snk_powers_process(snk_powers_obj * obj);

    void snk_powers_process_interface_blackhole(snk_powers_obj * obj);

    void snk_powers_process_format_undefined(snk_powers_obj * obj);

    snk_powers_cfg * snk_powers_cfg_construct(void);

    void snk_powers_cfg_destroy(snk_powers_cfg * snk_powers_config);

#endif