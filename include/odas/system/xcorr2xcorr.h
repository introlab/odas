#ifndef __ODAS_SYSTEM_XCORR
#define __ODAS_SYSTEM_XCORR

   /**
    * \file     xcorr2xcorr.h
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

    #include <signal/delta.h>
    #include <signal/xcorr.h>
    #include <signal/tdoa.h>
    #include <signal/pair.h>

    typedef struct xcorr2xcorr_obj {

        unsigned int frameSize;     ///< Number of samples per frame.

    } xcorr2xcorr_obj;

    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize);

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj);

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const deltas_obj * deltas, const pairs_obj * pairs, xcorrs_obj * xcorrsMax);

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const tdoas_obj * tdoas, const deltas_obj * deltas, const pairs_obj * pairs, const unsigned int iPoint, xcorrs_obj * xcorrs);

#endif
