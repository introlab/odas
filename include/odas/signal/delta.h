#ifndef __ODAS_SIGNAL_DELTA
#define __ODAS_SIGNAL_DELTA

   /**
    * \file     delta.h
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
    #include <string.h>

    typedef struct deltas_obj {

        unsigned int nPairs;
        unsigned int * array;

    } deltas_obj;

    deltas_obj * deltas_construct_zero(const unsigned int nPairs);

    deltas_obj * deltas_clone(const deltas_obj * obj);

    void deltas_destroy(deltas_obj * obj);

    void deltas_printf(const deltas_obj * obj);

#endif