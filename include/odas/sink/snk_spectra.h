#ifndef __ODAS_SINK_SPECTRA
#define __ODAS_SINK_SPECTRA

   /**
    * \file     snk_spectra.h
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