#ifndef __ODAS_SYSTEM_FREQ2FRAME
#define __ODAS_SYSTEM_FREQ2FRAME

   /**
    * \file     freq2frame.h
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

    #include <init/windowing.h>
    #include <signal/frame.h>
    #include <signal/freq.h>
    #include <signal/window.h>
    #include <utils/fft.h>

    typedef struct freq2frame_obj {

        unsigned int frameSize;
        unsigned int halfFrameSize;

        window_obj * win;
        float * frame;

        fft_obj * fft;

    } freq2frame_obj;

    freq2frame_obj * freq2frame_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    void freq2frame_destroy(freq2frame_obj * obj);

    void freq2frame_process(freq2frame_obj * obj, const freqs_obj * freqs, frames_obj * frames);

#endif
