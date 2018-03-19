#ifndef __ODAS_AMODULE_RESAMPLE
#define __ODAS_AMODULE_RESAMPLE

    /**
    * \file     amod_resample.h
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

    #include "../module/mod_resample.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_resample_obj {

        mod_resample_obj * mod_resample;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;    

    } amod_resample_obj;

    amod_resample_obj * amod_resample_construct(const mod_resample_cfg * mod_resample_config, const msg_hops_cfg * msg_hops_in_config, const msg_hops_cfg * msg_hops_out_config);

    void amod_resample_destroy(amod_resample_obj * obj);

    void amod_resample_connect(amod_resample_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_resample_disconnect(amod_resample_obj * obj);

    void * amod_resample_thread(void * ptr);    

#endif