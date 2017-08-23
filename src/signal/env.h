#ifndef __ODAS_SIGNAL_ENV
#define __ODAS_SIGNAL_ENV

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct envs_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        float ** array;

    } envs_obj;

    envs_obj * envs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    envs_obj * envs_clone(const envs_obj * obj);

    void envs_copy(envs_obj * dest, const envs_obj * src);

    void envs_zero(envs_obj * obj);

    void envs_destroy(envs_obj * obj);

    void envs_printf(const envs_obj * obj);

#endif