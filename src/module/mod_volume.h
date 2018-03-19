#ifndef __ODAS_MODULE_VOLUME
#define __ODAS_MODULE_VOLUME

   /**
    * \file     mod_volume.h
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

    #include "../system/hop2hop.h"
    #include "../message/msg_hops.h"

    typedef struct mod_volume_obj {

        hop2hop_gain_obj * hop2hop_gain;

        msg_hops_obj * in;
        msg_hops_obj * out;        

    } mod_volume_obj;

    typedef struct mod_volume_cfg {
        
        float gain;

    } mod_volume_cfg;

    mod_volume_obj * mod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config);

    void mod_volume_destroy(mod_volume_obj * obj);

    int mod_volume_process(mod_volume_obj * obj);

    void mod_volume_connect(mod_volume_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_volume_disconnect(mod_volume_obj * obj);

    mod_volume_cfg * mod_volume_cfg_construct(void);

    void mod_volume_cfg_destroy(mod_volume_cfg * cfg);

    void mod_volume_cfg_printf(const mod_volume_cfg * cfg);

#endif