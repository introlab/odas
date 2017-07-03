#ifndef __ODAS_SIGNAL_AREA
#define __ODAS_SIGNAL_AREA

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct areas_obj {

        unsigned int nPointsDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        float * array;

    } areas_obj;

    typedef struct area_obj {

        unsigned int nPairs;

        float * array;

    } area_obj;

    areas_obj * areas_construct_zero(const unsigned int nPointsDiscrete, const unsigned int nResolutionsPerDiscrete, const unsigned int nPairs);

    void areas_destroy(areas_obj * obj);

    void areas_printf(const areas_obj * obj);

    area_obj * area_construct_zero(const unsigned int nPairs);

    void area_destroy(area_obj * obj);

    void area_printf(const area_obj * obj);

#endif