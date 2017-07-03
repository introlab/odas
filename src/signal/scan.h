#ifndef __ODAS_SIGNAL_SCAN
#define __ODAS_SIGNAL_SCAN

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