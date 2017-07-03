#ifndef __ODAS_SIGNAL_HOP
#define __ODAS_SIGNAL_HOP

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct hops_obj {

        unsigned int nSignals; 
        unsigned int hopSize;
        float ** array;

    } hops_obj;

    hops_obj * hops_construct_zero(const unsigned int nSignals, const unsigned int hopSize);

    hops_obj * hops_clone(const hops_obj * obj);

    void hops_copy(hops_obj * dest, const hops_obj * src);

    void hops_zero(hops_obj * obj);

    void hops_destroy(hops_obj * obj);

    void hops_printf(const hops_obj * obj);

#endif