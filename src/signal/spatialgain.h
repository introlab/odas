#ifndef __ODAS_SIGNAL_SPATIALGAIN
#define __ODAS_SIGNAL_SPATIALGAIN

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct spatialgains_obj {

        unsigned int nChannels;
        unsigned int nPoints;
        
        float * array;

    } spatialgains_obj;

    spatialgains_obj * spatialgains_construct_zero(const unsigned int nChannels, const unsigned int nPoints);

    spatialgains_obj * spatialgains_clone(const spatialgains_obj * obj);

    void spatialgains_destroy(spatialgains_obj * obj);    

    void spatialgains_printf(const spatialgains_obj * obj);    

#endif