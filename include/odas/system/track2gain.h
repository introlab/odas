#ifndef __ODAS_SYSTEM_TRACK2GAIN
#define __ODAS_SYSTEM_TRACK2GAIN

   /**
    * \file     track2gain.h
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

    #include <signal/beampattern.h>
    #include <signal/track.h>
    #include <signal/gain.h>

    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    typedef struct track2gain_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float * directions;
        float * direction;

    } track2gain_obj;

    track2gain_obj * track2gain_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float * directions);

    void track2gain_destroy(track2gain_obj * obj);

    void track2gain_process(track2gain_obj * obj, const beampatterns_obj * beampatterns_mics, const tracks_obj * tracks, gains_obj * gains);


#endif
