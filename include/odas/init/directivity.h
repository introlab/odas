#ifndef __ODAS_INIT_DIRECTIVITY
#define __ODAS_INIT_DIRECTIVITY

   /**
    * \file     directivity.h
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
    #include <math.h>

    #include <general/mic.h>
    #include <general/spatialfilter.h>

    #include <signal/beampattern.h>
    #include <signal/pair.h>
    #include <signal/point.h>
    #include <signal/spatialgain.h>
    #include <signal/spatialindex.h>
    #include <signal/spatialmask.h>

    beampatterns_obj * directivity_beampattern_mics(const mics_obj * mics, const unsigned int nThetas);

    beampatterns_obj * directivity_beampattern_spatialfilters(const spatialfilters_obj * spatialfilters, const unsigned int nThetas);

    spatialgains_obj * directivity_spatialgains(const mics_obj * mics, const beampatterns_obj * beampatterns_mics, const spatialfilters_obj * spatialfilters, const beampatterns_obj * beampatterns_spatialfilter, const points_obj * points);

    spatialmasks_obj * directivity_spatialmasks(const spatialgains_obj * spatialgains, const float minGain);

    spatialindexes_obj * directivity_spatialindexes(const spatialmasks_obj * spatialmasks);

    pairs_obj * directivity_pairs(const spatialmasks_obj * spatialmasks);

    void directivity_pairsadd(pairs_obj * destPairs, const pairs_obj * srcPairs);

#endif
