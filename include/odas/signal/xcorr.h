#ifndef __ODAS_SIGNAL_XCORR
#define __ODAS_SIGNAL_XCORR

   /**
    * \file     xcorr.h
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
    #include <stdio.h>

    typedef struct xcorrs_obj {

        unsigned int nSignals;
        unsigned int frameSize;
        float ** array;

    } xcorrs_obj;

    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize);

    void xcorrs_destroy(xcorrs_obj * obj);

    void xcorrs_copy(xcorrs_obj * dest, const xcorrs_obj * src);

    void xcorrs_zero(xcorrs_obj * obj);

    void xcorrs_printf(const xcorrs_obj * obj);

    void xcorrs_printf_signal(const xcorrs_obj * obj, const unsigned int iSignal);

#endif