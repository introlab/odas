#ifndef __ODAS_SIGNAL_SPATIALINDEX
#define __ODAS_SIGNAL_SPATIALINDEX

   /**
    * \file     spatialindex.h
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

    typedef struct spatialindexes_obj {

        unsigned int nPoints;
        unsigned int nPairs;
        
        unsigned int * array;
        unsigned int * count;

    } spatialindexes_obj;

    spatialindexes_obj * spatialindexes_construct_zero(const unsigned int nPoints, const unsigned int nPairs);

    spatialindexes_obj * spatialindexes_clone(const spatialindexes_obj * obj);

    void spatialindexes_destroy(spatialindexes_obj * obj);    

    void spatialindexes_printf(const spatialindexes_obj * obj);

#endif