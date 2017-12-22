#ifndef __ODAS_SIGNAL_TDOA
#define __ODAS_SIGNAL_TDOA

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct tdoas_obj {

        unsigned int nPoints;
        unsigned int nPairs;
        unsigned int * array;
        unsigned int * min;
        unsigned int * max;

    } tdoas_obj;

    tdoas_obj * tdoas_construct_zero(const unsigned int nPoints, const unsigned int nPairs);

    void tdoas_destroy(tdoas_obj * obj);

    void tdoas_printf(const tdoas_obj * obj);

#endif