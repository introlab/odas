#ifndef __ODAS_SIGNAL_PITCH
#define __ODAS_SIGNAL_PITCH

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct pitches_obj {

        unsigned int nSignals;
        float * array;

    } pitches_obj;

    pitches_obj * pitches_construct_zero(const unsigned int nSignals);

    void pitches_destroy(pitches_obj * obj);

    void pitches_copy(pitches_obj * dest, const pitches_obj * src);

    void pitches_zero(pitches_obj * obj);

    void pitches_printf(const pitches_obj * obj);

#endif