#ifndef __ODAS_SIGNAL_ACORR
#define __ODAS_SIGNAL_ACORR

   /**
    * \file     acorr.h
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

    typedef struct acorrs_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        float ** array;

    } acorrs_obj;

    acorrs_obj * acorrs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    void acorrs_destroy(acorrs_obj * obj);

    void acorrs_copy(acorrs_obj * dest, const acorrs_obj * src);

    void acorrs_zero(acorrs_obj * obj);

    void acorrs_printf(const acorrs_obj * obj);

#endif