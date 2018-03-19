#ifndef __ODAS_ASOURCE_HOPS
#define __ODAS_ASOURCE_HOPS

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
    #include "../source/src_hops.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asrc_hops_obj {

        src_hops_obj * src_hops;
        amsg_hops_obj * out;
        thread_obj * thread;

    } asrc_hops_obj;

    asrc_hops_obj * asrc_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config);

    void asrc_hops_destroy(asrc_hops_obj * obj);

    void asrc_hops_connect(asrc_hops_obj * obj, amsg_hops_obj * out);

    void asrc_hops_disconnect(asrc_hops_obj * obj);

    void * asrc_hops_thread(void * ptr);

#endif