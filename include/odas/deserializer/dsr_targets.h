#ifndef __ODAS_DESERIALIZER_TARGETS
#define __ODAS_DESERIALIZER_TARGETS

   /**
    * \file     dsr_targets.h
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

    #include "../message/msg_targets.h"  

    #include "../utils/json.h" 
    #include "../utils/stringify.h"

    typedef struct dsr_targets_obj {

        unsigned long long timeStamp;

        unsigned int nTargets;
        unsigned int fS;

        json_tokens * tokens;
        char * string;

        char * in;
        msg_targets_obj * out;

    } dsr_targets_obj;

    typedef struct dsr_targets_cfg {

    } dsr_targets_cfg;

    dsr_targets_obj * dsr_targets_construct(const dsr_targets_cfg * dsr_targets_config, const msg_targets_cfg * msg_targets_config);

    void dsr_targets_destroy(dsr_targets_obj * obj);

    void dsr_targets_connect(dsr_targets_obj * obj, char * in, msg_targets_obj * out);

    void dsr_targets_disconnect(dsr_targets_obj * obj);

    void dsr_targets_process(dsr_targets_obj * obj);

    dsr_targets_cfg * dsr_targets_cfg_construct(void);

    void dsr_targets_cfg_destroy(dsr_targets_cfg * cfg);

#endif