#ifndef __ODAS_UTILS_GAUSSJORDAN
#define __ODAS_UTILS_GAUSSJORDAN

    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    typedef struct gaussjordan_obj {

        unsigned int nRowsCols;
        float * array;
        float epsilon;

    } gaussjordan_obj;

    gaussjordan_obj * gaussjordan_construct_zero(const unsigned int nRowsCols, const float epsilon);

    void gaussjordan_destroy(gaussjordan_obj * obj);

    void gaussjordan_process(gaussjordan_obj * obj, const float * src, float * dest);

#endif