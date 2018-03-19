#ifndef __ODAS_ACONNECTOR_CATEGORIES
#define __ODAS_ACONNECTOR_CATEGORIES

    /**
    * \file     acon_categories.h
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

    #include "../connector/con_categories.h"
    #include "../amessage/amsg_categories.h"
    #include "../message/msg_categories.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_categories_obj {

        amsg_categories_obj * in;
        amsg_categories_obj ** outs;
        con_categories_obj * con_categories;
        thread_obj * thread;

    } acon_categories_obj;

    acon_categories_obj * acon_categories_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_categories_cfg * msg_categories_config);

    void acon_categories_destroy(acon_categories_obj * obj);

    void * acon_categories_thread(void * ptr);

#endif