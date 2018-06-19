#ifndef __ODAS_SOURCE_TARGETS
#define __ODAS_SOURCE_TARGETS

   /**
    * \file     src_targets.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-12
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

    #include "../message/msg_targets.h"

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_targets.h"
    #include "../utils/json.h"

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct src_targets_obj {

        unsigned long long timeStamp;

        unsigned int nTargets;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        char * buffer;
        unsigned int bufferSize;

        json_tokens * tokens;

        targets_obj * targetsCst;

        msg_targets_obj * out;

    } src_targets_obj;

    typedef struct src_targets_cfg {

        format_obj * format;
        interface_obj * interface;

        targets_obj * targets;        

    } src_targets_cfg;

    src_targets_obj * src_targets_construct(const src_targets_cfg * src_targets_config, const msg_targets_cfg * msg_targets_config);

    void src_targets_destroy(src_targets_obj * obj);

    void src_targets_connect(src_targets_obj * obj, msg_targets_obj * out);

    void src_targets_disconnect(src_targets_obj * obj);

    void src_targets_open(src_targets_obj * obj);

    void src_targets_open_interface_blackhole(src_targets_obj * obj);

    void src_targets_open_interface_file(src_targets_obj * obj);

    void src_targets_open_interface_socket(src_targets_obj * obj);   

    void src_targets_close(src_targets_obj * obj);

    void src_targets_close_interface_blackhole(src_targets_obj * obj);

    void src_targets_close_interface_file(src_targets_obj * obj);

    void src_targets_close_interface_socket(src_targets_obj * obj);   
    
    int src_targets_process(src_targets_obj * obj);

    int src_targets_process_interface_blackhole(src_targets_obj * obj);

    int src_targets_process_interface_file(src_targets_obj * obj);

    int src_targets_process_interface_socket(src_targets_obj * obj);

    void src_targets_process_format_text_json(src_targets_obj * obj);

    src_targets_cfg * src_targets_cfg_construct(void);

    void src_targets_cfg_destroy(src_targets_cfg * cfg);

    void src_targets_cfg_printf(const src_targets_cfg * cfg);

#endif