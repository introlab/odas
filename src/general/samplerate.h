#ifndef __ODAS_GENERAL_SAMPLERATE
#define __ODAS_GENERAL_SAMPLERATE

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct samplerate_obj {

        unsigned int mu;
        float sigma2;

    } samplerate_obj;

    samplerate_obj * samplerate_construct_zero(void);

    samplerate_obj * samplerate_clone(const samplerate_obj * obj);

    void samplerate_destroy(samplerate_obj * obj);

    void samplerate_printf(const samplerate_obj * obj);

#endif