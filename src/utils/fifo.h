#ifndef __ODAS_UTILS_FIFO
#define __ODAS_UTILS_FIFO

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
    #include <string.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdio.h>

    typedef struct fifo_obj {

        void ** array;
        unsigned int nElements;
        unsigned int nMaxElements;

        pthread_mutex_t use;
        sem_t push;
        sem_t pop;

    } fifo_obj;

    fifo_obj * fifo_construct_zero(const unsigned int nMaxElements);

    void fifo_destroy(fifo_obj * obj);

    void fifo_push(fifo_obj * obj, void * element);

    void * fifo_pop(fifo_obj * obj);

    int fifo_nElements(fifo_obj * obj);

    void fifo_printf(const fifo_obj * obj);

#endif