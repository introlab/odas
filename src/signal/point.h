#ifndef __ODAS_SIGNAL_POINT
#define __ODAS_SIGNAL_POINT

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct points_obj {

        unsigned int nPoints;
        float * array;

    } points_obj;

    points_obj * points_construct_zero(const unsigned int nPoints);

    points_obj * points_clone(const points_obj * obj);

    void points_destroy(points_obj * obj);

    void points_printf(const points_obj * obj);

#endif