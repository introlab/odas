#ifndef __ODAS_SIGNAL_MAP
#define __ODAS_SIGNAL_MAP

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct maps_obj {

        unsigned int nCoarses;
        unsigned int nFines;
        char * array;

    } maps_obj;

    maps_obj * maps_construct_zero(const unsigned int nCoarses, const unsigned int nFines);

    void maps_destroy(maps_obj * obj);

    void maps_printf(const maps_obj * obj);

#endif