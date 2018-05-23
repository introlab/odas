#ifndef __ODAS_SIGNAL_SPATIALFILTER
#define __ODAS_SIGNAL_SPATIALFILTER

   /**
    * \file     spatialfilter.h
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

    typedef struct spatialfilters_obj {

        unsigned int nFilters;
        float * direction;
        float * thetaAllPass;
        float * thetaNoPass;

    } spatialfilters_obj;

    spatialfilters_obj * spatialfilters_construct_zero(unsigned int nFilters);

    spatialfilters_obj * spatialfilters_clone(const spatialfilters_obj * obj);

    void spatialfilters_destroy(spatialfilters_obj * obj); 

    void spatialfilters_printf(const spatialfilters_obj * obj);   

#endif