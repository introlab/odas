#ifndef __ODAS_SINK_SPECTRA
#define __ODAS_SINK_SPECTRA

   /**
    * \file     snk_spectra.h
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
    #include "../message/msg_spectra.h"

    typedef struct snk_spectra_obj {

        unsigned long long timeStamp;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        msg_spectra_obj * in;

    } snk_spectra_obj;

    typedef struct snk_spectra_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_spectra_cfg;

    snk_spectra_obj * snk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config);

    void snk_spectra_destroy(snk_spectra_obj * obj);

    void snk_spectra_connect(snk_spectra_obj * obj, msg_spectra_obj * in);

    void snk_spectra_disconnect(snk_spectra_obj * obj);

    void snk_spectra_open(snk_spectra_obj * obj);

    void snk_spectra_open_interface_blackhole(snk_spectra_obj * obj);

    void snk_spectra_close(snk_spectra_obj * obj);

    void snk_spectra_close_interface_blackhole(snk_spectra_obj * obj);

    int snk_spectra_process(snk_spectra_obj * obj);

    void snk_spectra_process_interface_blackhole(snk_spectra_obj * obj);

    void snk_spectra_process_format_undefined(snk_spectra_obj * obj);

    snk_spectra_cfg * snk_spectra_cfg_construct(void);

    void snk_spectra_cfg_destroy(snk_spectra_cfg * snk_spectra_config);

#endif