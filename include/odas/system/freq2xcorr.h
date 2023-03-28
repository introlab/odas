#ifndef __ODAS_SYSTEM_FREQ2XCORR
#define __ODAS_SYSTEM_FREQ2XCORR

   /**
    * \file     freq2xcorr.h
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

    #include <signal/frame.h>
    #include <signal/freq.h>
    #include <signal/pair.h>
    #include <signal/tdoa.h>
    #include <signal/xcorr.h>
    #include <utils/fft.h>

    typedef struct freq2xcorr_obj {

        unsigned int frameSize;
        unsigned int halfFrameSize;

        float * frame;

        fft_obj * fft;

    } freq2xcorr_obj;

    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    void freq2xcorr_destroy(freq2xcorr_obj * obj);

    void freq2xcorr_process(freq2xcorr_obj * obj, const freqs_obj * freqs, const pairs_obj * pairs, xcorrs_obj * xcorrs);

#endif
