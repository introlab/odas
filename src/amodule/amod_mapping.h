#ifndef __ODAS_AMODULE_MAPPING
#define __ODAS_AMODULE_MAPPING

    /**
    * \file     amod_mapping.h
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

    #include "../module/mod_mapping.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_mapping_obj {

        mod_mapping_obj * mod_mapping;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;        

    } amod_mapping_obj;

    amod_mapping_obj * amod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config);

    void amod_mapping_destroy(amod_mapping_obj * obj);

    void amod_mapping_connect(amod_mapping_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_mapping_disconnect(amod_mapping_obj * obj);

    void * amod_mapping_thread(void * ptr);    

#endif