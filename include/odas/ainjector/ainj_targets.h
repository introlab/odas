#ifndef __ODAS_AINJECTOR_TARGETS
#define __ODAS_AINJECTOR_TARGETS

    /**
    * \file     ainj_targets.h
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

    #include "../injector/inj_targets.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_targets.h"
    #include "../general/thread.h"

    typedef struct ainj_targets_obj {

        inj_targets_obj * inj_targets;
        amsg_hops_obj * in;
        amsg_targets_obj * out;
        thread_obj * thread;    

    } ainj_targets_obj;

    ainj_targets_obj * ainj_targets_construct(const inj_targets_cfg * inj_targets_config, const msg_hops_cfg * msg_hops_config, const msg_targets_cfg * msg_targets_config);

    void ainj_targets_destroy(ainj_targets_obj * obj);

    void ainj_targets_connect(ainj_targets_obj * obj, amsg_hops_obj * in, amsg_targets_obj * out);

    void ainj_targets_disconnect(ainj_targets_obj * obj);

    void * ainj_targets_thread(void * ptr); 

#endif