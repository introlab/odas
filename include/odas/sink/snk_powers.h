#ifndef __ODAS_SINK_POWERS
#define __ODAS_SINK_POWERS

   /**
    * \file     snk_powers.h
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