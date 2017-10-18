#ifndef __ODAS_SIGNAL_CATEGORY
#define __ODAS_SIGNAL_CATEGORY

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct categories_obj {

        unsigned int nSignals;
        char * array;

    } categories_obj;

    categories_obj * categories_construct_zero(const unsigned int nSignals);

    void categories_destroy(categories_obj * obj);

    void categories_printf(const categories_obj * obj);

#endif