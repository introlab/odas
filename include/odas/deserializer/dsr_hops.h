#ifndef __ODAS_DESERIALIZER_HOPS
#define __ODAS_DESERIALIZER_HOPS

   /**
    * \file     dsr_hops.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-06
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

    #include "../utils/json.h" 
    #include "../utils/stringify.h"

    typedef struct dsr_hops_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

        json_tokens * tokens;
        char ** samples;

        char * in;
        msg_hops_obj * out;

    } dsr_hops_obj;

    typedef struct dsr_hops_cfg {

    } dsr_hops_cfg;

    dsr_hops_obj * dsr_hops_construct(const dsr_hops_cfg * dsr_hops_config, const msg_hops_cfg * msg_hops_config);

    void dsr_hops_destroy(dsr_hops_obj * obj);

    void dsr_hops_connect(dsr_hops_obj * obj, char * in, msg_hops_obj * out);

    void dsr_hops_disconnect(dsr_hops_obj * obj);

    void dsr_hops_process(dsr_hops_obj * obj);

    dsr_hops_cfg * dsr_hops_cfg_construct(void);

    void dsr_hops_cfg_destroy(dsr_hops_cfg * cfg);

#endif