#ifndef __ODAS_SIGNAL_IMPULSE
#define __ODAS_SIGNAL_IMPULSE

    #include <stdlib.h>
    #include <string.h>

    typedef struct impulse_obj {

        float * array;
        unsigned int nCoefficients;

    } impulse_obj;

    impulse_obj * impulse_construct(const unsigned int nCoefficients);

    void impulse_destroy(impulse_obj * obj);

#endif