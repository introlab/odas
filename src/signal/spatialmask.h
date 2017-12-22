#ifndef __ODAS_SIGNAL_SPATIALMASK
#define __ODAS_SIGNAL_SPATIALMASK

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct spatialmasks_obj {

        unsigned int nPoints;
        unsigned int nPairs;
        
        char * array;

    } spatialmasks_obj;

    spatialmasks_obj * spatialmasks_construct_zero(const unsigned int nPoints, const unsigned int nPairs);

    spatialmasks_obj * spatialmasks_clone(const spatialmasks_obj * obj);

    void spatialmasks_destroy(spatialmasks_obj * obj); 

    void spatialmasks_printf(const spatialmasks_obj * obj);   

#endif