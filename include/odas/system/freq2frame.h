#ifndef __ODAS_SYSTEM_FREQ2FRAME
#define __ODAS_SYSTEM_FREQ2FRAME

   /**
    * \file     freq2frame.h
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
