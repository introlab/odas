#ifndef __ODAS_UTILS_LATCH
#define __ODAS_UTILS_LATCH

   /**
    * \file     fifo.h
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

    #include <stdlib.h>
    #include <stdio.h>
    #include <pthread.h>

    typedef struct share_obj {

        void * ptr;
        pthread_mutex_t use;

    } share_obj;

    share_obj * share_construct(void * ptr);

    void share_destroy(share_obj * obj);

    void * share_get(share_obj * obj);

    void share_release(share_obj * obj, void * ptr);

#endif