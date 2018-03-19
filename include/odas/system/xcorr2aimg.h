#ifndef __ODAS_SYSTEM_XCORR2AIMG
#define __ODAS_SYSTEM_XCORR2AIMG

   /**
    * \file     xcorr2aimg.h
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

    #include <signal/tdoa.h>
    #include <signal/index.h>
    #include <signal/xcorr.h>
    #include <signal/aimg.h>
    #include <signal/spatialindex.h>

    //! Update the states of the particle filter
    typedef struct xcorr2aimg_obj {

        unsigned int aimgSize;      ///< Number of points scanned.

    } xcorr2aimg_obj;

    xcorr2aimg_obj * xcorr2aimg_construct_zero(const unsigned int aimgSize);

    void xcorr2aimg_destroy(xcorr2aimg_obj * obj);

    void xcorr2aimg_process(xcorr2aimg_obj * obj, const tdoas_obj * tdoas, const indexes_obj * indexes, const spatialindexes_obj * spatialindexes, const unsigned int iCoarse, const xcorrs_obj * xcorrs, aimg_obj * aimg);

#endif
