#ifndef __ODAS_SYSTEM_XCORR
#define __ODAS_SYSTEM_XCORR

   /**
    * \file     xcorr2xcorr.h
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
