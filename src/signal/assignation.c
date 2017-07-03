    
    #include "assignation.h"

    assignations_obj * assignations_construct_zero(const unsigned int nAssignations, const unsigned int nPots) {

    	assignations_obj * obj;

        obj = (assignations_obj *) malloc(sizeof(assignations_obj));

        obj->nAssignations = nAssignations;
        obj->nPots = nPots;
        obj->array = (signed int *) malloc(sizeof(signed int) * nAssignations * nPots);
        memset(obj->array, 0x00, nAssignations * nPots * sizeof(signed int));

    	return obj;

    }

    void assignations_destroy(assignations_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void assignations_printf(const assignations_obj * obj) {

        unsigned int iAssignation;
        unsigned int iPot;

        for (iAssignation = 0; iAssignation < obj->nAssignations; iAssignation++) {

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+01d ",obj->array[iAssignation * obj->nPots + iPot]);

            }

            printf("\n");

        }

    }
