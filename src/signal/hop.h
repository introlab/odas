#ifndef __ODAS_SIGNAL_HOP
#define __ODAS_SIGNAL_HOP

   /**
    * \file     hop.h
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
    #include <stdio.h>

    typedef struct hops_obj {

        unsigned int nSignals; 
        unsigned int hopSize;
        float ** array;

    } hops_obj;

    hops_obj * hops_construct_zero(const unsigned int nSignals, const unsigned int hopSize);

    hops_obj * hops_clone(const hops_obj * obj);

    void hops_copy(hops_obj * dest, const hops_obj * src);

    void hops_zero(hops_obj * obj);

    void hops_destroy(hops_obj * obj);

    void hops_printf(const hops_obj * obj);

#endif