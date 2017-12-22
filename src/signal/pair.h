#ifndef __ODAS_SIGNAL_PAIR
#define __ODAS_SIGNAL_PAIR

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct pairs_obj {

        unsigned int nPairs;
        char * array;

    } pairs_obj;

    pairs_obj * pairs_construct_zero(const unsigned int nPairs);

    pairs_obj * pairs_clone(const pairs_obj * obj);

    void pairs_destroy(pairs_obj * obj);

    void pairs_printf(const pairs_obj * obj);

#endif