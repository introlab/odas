#ifndef __ODAS_SIGNAL_ASSIGNATION
#define __ODAS_SIGNAL_ASSIGNATION

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct assignations_obj {

        unsigned int nAssignations;
        unsigned int nPots;
        signed int * array;

    } assignations_obj;

    assignations_obj * assignations_construct_zero(const unsigned int nAssignations, const unsigned int nPots);

    void assignations_destroy(assignations_obj * obj);

    void assignations_printf(const assignations_obj * obj);

#endif