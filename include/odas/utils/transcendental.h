#ifndef __ODAS_UTILS_TRANSCENDENTAL
#define __ODAS_UTILS_TRANSCENDENTAL

   /**
    * \file     transcendental.h
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
    #include <math.h>

    typedef struct transcendental_obj {

        float maxValue;
        float minValue;
        float interval;

        float * array;
        unsigned int nElements;

    } transcendental_obj;

    transcendental_obj * transcendental_construct_zero(const float minValue, const float maxValue, const unsigned int nElements);

    void transcendental_destroy(transcendental_obj * obj);

    float transcendental_process(const transcendental_obj * obj, const float value);

#endif