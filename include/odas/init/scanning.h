#ifndef __ODAS_INIT_SCANNING
#define __ODAS_INIT_SCANNING

   /**
    * \file     scanning.h
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

    #include <general/mic.h>
    #include <general/soundspeed.h>
    #include <general/spatialfilter.h>

    #include <signal/beampattern.h>
    #include <signal/scan.h>
    #include <signal/spatialgain.h>
    #include <signal/spatialindex.h>
    #include <signal/spatialmask.h>
    #include <signal/map.h>
    #include <signal/pair.h>
    #include <signal/tau.h>

    #include <init/delay.h>
    #include <init/directivity.h>
    #include <init/hit.h>
    #include <init/linking.h>
    #include <init/space.h>

    scans_obj * scanning_init_scans(const mics_obj * mics, const spatialfilters_obj * spatialfilters, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const unsigned int nMatches, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels, const unsigned int nThetas, const float gainMin, const unsigned int interpRate);

#endif
