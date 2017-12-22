#ifndef __ODAS_SIGNAL_STEER
#define __ODAS_SIGNAL_STEER

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct steers_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        float ** array;

    } steers_obj;

    steers_obj * steers_construct_zero(const unsigned int halfFrameSize, const unsigned int nSeps, const unsigned int nChannels);

    void steers_destroy(steers_obj * obj);

    void steers_copy(steers_obj * dest, const steers_obj * src);

    void steers_printf(const steers_obj * obj);

#endif