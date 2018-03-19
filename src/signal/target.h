#ifndef __ODAS_SIGNAL_TARGET
#define __ODAS_SIGNAL_TARGET

   /**
    * \file     target.h
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

    typedef struct targets_obj {

        unsigned int nTargets;
        char ** tags;
        float * array;
        
    } targets_obj;

    targets_obj * targets_construct_zero(const unsigned int nTargets);

    void targets_destroy(targets_obj * obj);

    targets_obj * targets_clone(const targets_obj * obj);

    void targets_copy(targets_obj * dest, const targets_obj * src);

    void targets_zero(targets_obj * obj);

    void targets_printf(const targets_obj * obj);    

#endif