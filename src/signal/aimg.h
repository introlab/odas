#ifndef __ODAS_SIGNAL_AIMG
#define __ODAS_SIGNAL_AIMG

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct aimg_obj {

        unsigned int aimgSize;
        float * array;

    } aimg_obj;

    aimg_obj * aimg_construct_zero(const unsigned int aimgSize);

    void aimg_destroy(aimg_obj * obj);

    void aimg_printf(const aimg_obj * obj);

#endif