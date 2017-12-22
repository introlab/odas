#ifndef __ODAS_SIGNAL_POT
#define __ODAS_SIGNAL_POT

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct pots_obj {

        unsigned int nPots;
        float * array;

    } pots_obj;

    pots_obj * pots_construct_zero(const unsigned int nPots);

    pots_obj * pots_clone(const pots_obj * obj);

    void pots_copy(pots_obj * dest, const pots_obj * src);

    void pots_zero(pots_obj * obj);

    void pots_destroy(pots_obj * obj);

    void pots_printf(const pots_obj * obj);

#endif