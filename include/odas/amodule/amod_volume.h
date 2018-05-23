#ifndef __ODAS_AMODULE_VOLUME
#define __ODAS_AMODULE_VOLUME

    /**
    * \file     amod_volume.h
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

    #include "../module/mod_volume.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_volume_obj {

        mod_volume_obj * mod_volume;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;        

    } amod_volume_obj;

    amod_volume_obj * amod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config);

    void amod_volume_destroy(amod_volume_obj * obj);

    void amod_volume_connect(amod_volume_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_volume_disconnect(amod_volume_obj * obj);

    void amod_volume_enable(amod_volume_obj * obj);

    void amod_volume_disable(amod_volume_obj * obj);

    void * amod_volume_thread(void * ptr);    

#endif