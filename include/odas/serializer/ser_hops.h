#ifndef __ODAS_SERIALIZER_HOPS
#define __ODAS_SERIALIZER_HOPS

   /**
    * \file     ser_hops.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-08
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

    #include "../message/msg_hops.h"  

    #include "../utils/stringify.h"

    typedef struct ser_hops_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

        char * string;

        msg_hops_obj * in;
        char * out;

    } ser_hops_obj;

    typedef struct ser_hops_cfg {

    } ser_hops_cfg;

    ser_hops_obj * ser_hops_construct(const ser_hops_cfg * ser_hops_config, const msg_hops_cfg * msg_hops_config);

    void ser_hops_destroy(ser_hops_obj * obj);

    void ser_hops_connect(ser_hops_obj * obj, msg_hops_obj * in, char * out);

    void ser_hops_disconnect(ser_hops_obj * obj);

    void ser_hops_process(ser_hops_obj * obj);

    ser_hops_cfg * ser_hops_cfg_construct(void);

    void ser_hops_cfg_destroy(ser_hops_cfg * cfg);

#endif