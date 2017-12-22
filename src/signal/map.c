
    #include "map.h"

    maps_obj * maps_construct_zero(const unsigned int nCoarses, const unsigned int nFines) {

        maps_obj * obj;

        obj = (maps_obj *) malloc(sizeof(maps_obj));

        obj->nCoarses = nCoarses;
        obj->nFines = nFines;
        
        obj->array = (char *) malloc(sizeof(char) * nFines * nCoarses);
        memset(obj->array, 0x00, sizeof(char) * nFines * nCoarses);

        return obj;

    }

    void maps_destroy(maps_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void maps_printf(const maps_obj * obj) {

        unsigned int iFine;
        unsigned int iCoarse;

        for (iFine = 0; iFine < obj->nFines; iFine++) {

            printf("(%04u): ",iFine);

            for (iCoarse = 0; iCoarse < obj->nCoarses; iCoarse++) {

                printf("%01u",obj->array[iFine * obj->nCoarses + iCoarse]);

            }

            printf("\n");

        }

    }