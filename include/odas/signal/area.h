#ifndef __ODAS_SIGNAL_AREA
#define __ODAS_SIGNAL_AREA

   /**
    * \file     area.h
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

    typedef struct areas_obj {

        unsigned int nPointsDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        float * array;

    } areas_obj;

    typedef struct area_obj {

        unsigned int nPairs;

        float * array;

    } area_obj;

    areas_obj * areas_construct_zero(const unsigned int nPointsDiscrete, const unsigned int nResolutionsPerDiscrete, const unsigned int nPairs);

    void areas_destroy(areas_obj * obj);

    void areas_printf(const areas_obj * obj);

    area_obj * area_construct_zero(const unsigned int nPairs);

    void area_destroy(area_obj * obj);

    void area_printf(const area_obj * obj);

#endif