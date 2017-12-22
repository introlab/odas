#ifndef __ODAS_SIGNAL_DEMIXING
#define __ODAS_SIGNAL_DEMIXING

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct demixings_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        float ** array;

    } demixings_obj;

    demixings_obj * demixings_construct_zero(const unsigned int halfFrameSize, const unsigned int nSeps, const unsigned int nChannels);

    void demixings_destroy(demixings_obj * obj);

    void demixings_copy(demixings_obj * dest, const demixings_obj * src);

    void demixings_zero(demixings_obj * obj);

    void demixings_printf(const demixings_obj * obj);

#endif