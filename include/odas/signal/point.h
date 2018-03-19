#ifndef __ODAS_SIGNAL_POINT
#define __ODAS_SIGNAL_POINT

   /**
    * \file     point.h
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

    typedef struct points_obj {

        unsigned int nPoints;
        float * array;

    } points_obj;

    points_obj * points_construct_zero(const unsigned int nPoints);

    points_obj * points_clone(const points_obj * obj);

    void points_destroy(points_obj * obj);

    void points_printf(const points_obj * obj);

#endif