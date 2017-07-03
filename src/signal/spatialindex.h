#ifndef __ODAS_SIGNAL_SPATIALINDEX
#define __ODAS_SIGNAL_SPATIALINDEX

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct spatialindexes_obj {

        unsigned int nPoints;
        unsigned int nPairs;
        
        unsigned int * array;
        unsigned int * count;

    } spatialindexes_obj;

    spatialindexes_obj * spatialindexes_construct_zero(const unsigned int nPoints, const unsigned int nPairs);

    spatialindexes_obj * spatialindexes_clone(const spatialindexes_obj * obj);

    void spatialindexes_destroy(spatialindexes_obj * obj);    

    void spatialindexes_printf(const spatialindexes_obj * obj);

#endif