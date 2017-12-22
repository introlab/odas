#ifndef __ODAS_SIGNAL_TARGET
#define __ODAS_SIGNAL_TARGET

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct targets_obj {

        unsigned int nTargets;
        char ** tags;
        float * array;
        
    } targets_obj;

    targets_obj * targets_construct_zero(const unsigned int nTargets);

    void targets_destroy(targets_obj * obj);

    targets_obj * targets_clone(const targets_obj * obj);

    void targets_copy(targets_obj * dest, const targets_obj * src);

    void targets_zero(targets_obj * obj);

    void targets_printf(const targets_obj * obj);    

#endif