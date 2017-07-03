#ifndef __ODAS_SIGNAL_TAU
#define __ODAS_SIGNAL_TAU

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct taus_obj {

        unsigned int nPoints;
        unsigned int nPairs;
        float * mu;
        float * sigma2;

    } taus_obj;

    taus_obj * taus_construct_zero(const unsigned int nPoints, const unsigned int nPairs);

    void taus_destroy(taus_obj * obj);

    void taus_printf(const taus_obj * obj);

#endif