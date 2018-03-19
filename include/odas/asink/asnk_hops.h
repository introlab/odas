#ifndef __ODAS_ASINK_HOPS
#define __ODAS_ASINK_HOPS

    /**
    * \file     asink_hops.h
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
    #include "../sink/snk_hops.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_hops_obj {

        snk_hops_obj * snk_hops;
        amsg_hops_obj * in;
        thread_obj * thread;

    } asnk_hops_obj;

    asnk_hops_obj * asnk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config);

    void asnk_hops_destroy(asnk_hops_obj * obj);

    void asnk_hops_connect(asnk_hops_obj * obj, amsg_hops_obj * in);

    void asnk_hops_disconnect(asnk_hops_obj * obj);

    void * asnk_hops_thread(void * ptr);

#endif