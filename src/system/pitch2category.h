#ifndef __ODAS_SYSTEM_PITCH2CATEGORY
#define __ODAS_SYSTEM_PITCH2CATEGORY

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/category.h"
    #include "../signal/pitch.h"
    #include "../signal/track.h"
    
    typedef struct pitch2category_obj {

        unsigned int nSeps;

        float tauMin;
        float tauMax;
        float deltaTauMax;
        float alpha;
        float gamma;
        float phiMin;
        float r0;

        float * tausNow;
        float * tausPrev;
        float * deltaTausNow;
        float * deltaTausPrev;
        float * phisNow;
        float * phisPrev;
        float * vs;
        float * rs;
        char * categories;

    } pitch2category_obj;

    pitch2category_obj * pitch2category_construct_zero(const unsigned int nSeps, const float tauMin, const float tauMax, const float deltaTauMax, const float alpha, const float gamma, const float phiMin, const float r0);

    void pitch2category_destroy(pitch2category_obj * obj);

    void pitch2category_process(pitch2category_obj * obj, const pitches_obj * pitches, const tracks_obj * tracks, categories_obj * categories);

#endif