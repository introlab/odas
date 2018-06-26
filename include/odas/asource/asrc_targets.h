#ifndef __ODAS_ASOURCE_TARGETS
#define __ODAS_ASOURCE_TARGETS

    /**
    * \file     asource_hops.h
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

    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_targets.h"
    #include "../source/src_targets.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asrc_targets_obj {

        src_targets_obj * src_targets;
        amsg_hops_obj * in;
        amsg_targets_obj * out;
        thread_obj * thread;
        thread_obj * thread_receive;
        thread_obj * thread_process;

    } asrc_targets_obj;

    asrc_targets_obj * asrc_targets_construct(const src_targets_cfg * src_targets_config, const msg_targets_cfg * msg_targets_config);

    void asrc_targets_destroy(asrc_targets_obj * obj);

    void asrc_targets_connect(asrc_targets_obj * obj, amsg_hops_obj * in, amsg_targets_obj * out);

    void asrc_targets_disconnect(asrc_targets_obj * obj);

    void * asrc_targets_thread_receive(void * ptr);

    void * asrc_targets_thread_process(void * ptr);

    void * asrc_targets_thread(void * ptr);

#endif