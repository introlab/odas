#ifndef __ODAS_SIGNAL_TRIANGLE
#define __ODAS_SIGNAL_TRIANGLE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct triangles_obj {

        unsigned nTriangles;
        float * array;

    } triangles_obj;

    triangles_obj * triangles_construct_zero(const unsigned int nTriangles);

    void triangles_destroy(triangles_obj * obj);

    void triangles_printf(const triangles_obj * obj);

#endif