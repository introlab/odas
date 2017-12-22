#ifndef __ODAS_SIGNAL_MASK
#define __ODAS_SIGNAL_MASK

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct masks_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        char * array;               

    } masks_obj;

    masks_obj * masks_construct_zero(const unsigned int nSeps, const unsigned int nChannels);

    void masks_destroy(masks_obj * obj);    

    void masks_printf(const masks_obj * obj);

#endif