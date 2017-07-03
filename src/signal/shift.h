#ifndef __ODAS_SIGNAL_SHIFT
#define __ODAS_SIGNAL_SHIFT

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct shifts_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float * array;

    } shifts_obj;

    shifts_obj * shifts_construct_zero(const unsigned int nSeps, const unsigned int nChannels);

    void shifts_destroy(shifts_obj * obj);

    void shifts_printf(const shifts_obj * obj);

#endif