#ifndef __ODAS_SIGNAL_MASK
#define __ODAS_SIGNAL_MASK

   /**
    * \file     mask.h
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

    typedef struct masks_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        char * array;               

    } masks_obj;

    masks_obj * masks_construct_zero(const unsigned int nSeps, const unsigned int nChannels);

    void masks_copy(masks_obj * dest, const masks_obj * src);

    void masks_zero(masks_obj * obj);

    void masks_destroy(masks_obj * obj);

    void masks_printf(const masks_obj * obj);

#endif