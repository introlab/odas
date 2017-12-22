#ifndef __ODAS_GENERAL_MIC
#define __ODAS_GENERAL_MIC

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct mics_obj {

        unsigned int nChannels;
        unsigned int nPairs;
        float * mu;
        float * sigma2;
        float * direction;
        float * thetaAllPass;
        float * thetaNoPass;

    } mics_obj;

    mics_obj * mics_construct_zero(const unsigned int nChannels);

    mics_obj * mics_clone(const mics_obj * obj);

    void mics_destroy(mics_obj * obj);

    void mics_printf(const mics_obj * obj);

#endif