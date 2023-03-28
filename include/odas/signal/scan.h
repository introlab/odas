#ifndef __ODAS_SIGNAL_SCAN
#define __ODAS_SIGNAL_SCAN

   /**
    * \file     scan.h
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

    #include "pair.h"
    #include "point.h"
    #include "tdoa.h"
    #include "delta.h"
    #include "index.h"
    #include "spatialindex.h"

    //! Scan setup
    typedef struct scans_obj {

        unsigned int nLevels;

        points_obj ** points;
        tdoas_obj ** tdoas;
        deltas_obj ** deltas;
        spatialindexes_obj ** spatialindexes;
        pairs_obj * pairs;

        indexes_obj ** indexes;       

    } scans_obj;

    scans_obj * scans_construct_null(const unsigned int nLevels);

    void scans_destroy(scans_obj * obj);

#endif