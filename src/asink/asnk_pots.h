#ifndef __ODAS_ASINK_POTS
#define __ODAS_ASINK_POTS

    /**
    * \file     asink_pots.h
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

    #include "../amessage/amsg_pots.h"
    #include "../sink/snk_pots.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_pots_obj {

        snk_pots_obj * snk_pots;
        amsg_pots_obj * in;
        thread_obj * thread;

    } asnk_pots_obj;

    asnk_pots_obj * asnk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config);

    void asnk_pots_destroy(asnk_pots_obj * obj);

    void asnk_pots_connect(asnk_pots_obj * obj, amsg_pots_obj * in);

    void asnk_pots_disconnect(asnk_pots_obj * obj);

    void * asnk_pots_thread(void * ptr);

#endif