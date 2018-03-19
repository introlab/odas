#ifndef __ODAS_SIGNAL_DEMIXING
#define __ODAS_SIGNAL_DEMIXING

   /**
    * \file     demixing.h
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

    typedef struct demixings_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        float ** array;

    } demixings_obj;

    demixings_obj * demixings_construct_zero(const unsigned int halfFrameSize, const unsigned int nSeps, const unsigned int nChannels);

    void demixings_destroy(demixings_obj * obj);

    void demixings_copy(demixings_obj * dest, const demixings_obj * src);

    void demixings_zero(demixings_obj * obj);

    void demixings_printf(const demixings_obj * obj);

#endif