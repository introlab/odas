#ifndef __ODAS_SIGNAL_GAIN
#define __ODAS_SIGNAL_GAIN

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct gains_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float * array;        

    } gains_obj;

    gains_obj * gains_construct_zero(const unsigned int nSeps, const unsigned int nChannels);

    void gains_destroy(gains_obj * obj);

    void gains_printf(const gains_obj * obj);

#endif