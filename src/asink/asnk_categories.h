#ifndef __ODAS_ASINK_CATEGORIES
#define __ODAS_ASINK_CATEGORIES

    /**
    * \file     asink_categories.h
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

    #include "../amessage/amsg_categories.h"
    #include "../sink/snk_categories.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_categories_obj {

        snk_categories_obj * snk_categories;
        amsg_categories_obj * in;
        thread_obj * thread;

    } asnk_categories_obj;

    asnk_categories_obj * asnk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config);

    void asnk_categories_destroy(asnk_categories_obj * obj);

    void asnk_categories_connect(asnk_categories_obj * obj, amsg_categories_obj * in);

    void asnk_categories_disconnect(asnk_categories_obj * obj);

    void * asnk_categories_thread(void * ptr);

#endif