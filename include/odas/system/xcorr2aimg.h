#ifndef __ODAS_SYSTEM_XCORR2AIMG
#define __ODAS_SYSTEM_XCORR2AIMG

   /**
    * \file     xcorr2aimg.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
