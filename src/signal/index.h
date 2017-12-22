#ifndef __ODAS_SIGNAL_INDEX
#define __ODAS_SIGNAL_INDEX

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct indexes_obj {

        unsigned int nCoarses;
        unsigned int nFines;
        unsigned int * array;
        unsigned int * count;

    } indexes_obj;

    indexes_obj * indexes_construct_zero(const unsigned int nCoarses, const unsigned int nFines);

    void indexes_destroy(indexes_obj * obj);

    void indexes_printf(const indexes_obj * obj);

#endif