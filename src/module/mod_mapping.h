#ifndef __ODAS_MODULE_MAPPING
#define __ODAS_MODULE_MAPPING

   /**
    * \file     mod_mapping.h
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

    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    #include "../general/link.h"
    #include "../system/hop2hop.h"

    typedef struct mod_mapping_obj {

        hop2hop_multiplex_obj * hop2hop_multiplex;
        links_obj * links;

        msg_hops_obj * in;
        msg_hops_obj * out;

    } mod_mapping_obj;

    typedef struct mod_mapping_cfg {
        
        links_obj * links;

    } mod_mapping_cfg;

    mod_mapping_obj * mod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config);

    void mod_mapping_destroy(mod_mapping_obj * obj);

    int mod_mapping_process(mod_mapping_obj * obj);

    void mod_mapping_connect(mod_mapping_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_mapping_disconnect(mod_mapping_obj * obj);

    mod_mapping_cfg * mod_mapping_cfg_construct(void);

    void mod_mapping_cfg_destroy(mod_mapping_cfg * cfg);

    void mod_mapping_cfg_printf(const mod_mapping_cfg * cfg);

#endif