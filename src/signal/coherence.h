#ifndef __ODAS_SIGNAL_COHERENCE
#define __ODAS_SIGNAL_COHERENCE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct coherences_obj {

        unsigned int nTracks;
        unsigned int nPots;
        float * array;

    } coherences_obj;

    coherences_obj * coherences_construct_zero(const unsigned int nTracks, const unsigned int nPots);

    void coherences_destroy(coherences_obj * obj);

    void coherences_printf(coherences_obj * obj);

#endif