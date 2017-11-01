#ifndef __ODAS_UTILS_TRANSCENDENTAL
#define __ODAS_UTILS_TRANSCENDENTAL

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    typedef struct transcendental_obj {

        float maxValue;
        float minValue;
        float interval;

        float * array;
        unsigned int nElements;

    } transcendental_obj;

    transcendental_obj * transcendental_construct_zero(const float minValue, const float maxValue, const unsigned int nElements);

    void transcendental_destroy(transcendental_obj * obj);

    float transcendental_process(const transcendental_obj * obj, const float value);

#endif