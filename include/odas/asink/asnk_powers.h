#ifndef __ODAS_ASINK_POWERS
#define __ODAS_ASINK_POWERS

    /**
    * \file     asink_powers.h
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

    #include "../amessage/amsg_powers.h"
    #include "../sink/snk_powers.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_powers_obj {

        snk_powers_obj * snk_powers;
        amsg_powers_obj * in;
        thread_obj * thread;

    } asnk_powers_obj;

    asnk_powers_obj * asnk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config);

    void asnk_powers_destroy(asnk_powers_obj * obj);

    void asnk_powers_connect(asnk_powers_obj * obj, amsg_powers_obj * in);

    void asnk_powers_disconnect(asnk_powers_obj * obj);

    void * asnk_powers_thread(void * ptr);

#endif