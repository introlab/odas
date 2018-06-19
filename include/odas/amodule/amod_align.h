#ifndef __ODAS_AMODULE_ALIGN
#define __ODAS_AMODULE_ALIGN

    /**
    * \file     amod_align.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-24
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

    #include "../module/mod_align.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_targets.h"
    #include "../general/thread.h"

    typedef struct amod_align_obj {

        mod_align_obj * mod_align;
        amsg_targets_obj * in1;
        amsg_hops_obj * in2;
        amsg_hops_obj * in3;
        amsg_targets_obj * out;
        thread_obj * thread;        

    } amod_align_obj;

    amod_align_obj * amod_align_construct(const mod_align_cfg * mod_align_config, const msg_targets_cfg * msg_targets_in_config, const msg_hops_cfg * msg_hops_in_config, const msg_targets_cfg * msg_targets_out_config);

    void amod_align_destroy(amod_align_obj * obj);

    void amod_align_connect(amod_align_obj * obj, amsg_targets_obj * in1, amsg_hops_obj * in2, amsg_targets_obj * out);

    void amod_align_disconnect(amod_align_obj * obj);

    void amod_align_enable(amod_align_obj * obj);

    void amod_align_disable(amod_align_obj * obj);

    void * amod_align_thread(void * ptr);    

#endif