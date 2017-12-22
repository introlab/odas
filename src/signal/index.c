    
    #include "index.h"

    indexes_obj * indexes_construct_zero(const unsigned int nCoarses, const unsigned int nFines) {

        indexes_obj * obj;

        obj = (indexes_obj *) malloc(sizeof(indexes_obj));

        obj->nCoarses = nCoarses;
        obj->nFines = nFines;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nCoarses * nFines);
        memset(obj->array, 0x00, sizeof(unsigned int) * nCoarses * nFines);
        obj->count = (unsigned int *) malloc(sizeof(unsigned int) * nCoarses);
        memset(obj->count, 0x00, sizeof(unsigned int) * nCoarses);

        return obj;

    }

    void indexes_destroy(indexes_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->count);
        free((void *) obj);

    }

    void indexes_printf(const indexes_obj * obj) {

        unsigned int iCoarse;
        unsigned int iFine;

        for (iCoarse = 0; iCoarse < obj->nCoarses; iCoarse++) {

            printf("(%04u): ",iCoarse);

            if (obj->count[iCoarse] > 0) {

                for (iFine = 0; iFine < obj->count[iCoarse]; iFine++) {

                    printf("%04u ",obj->array[iCoarse * obj->nFines + iFine]);

                }

            }
            else {

                printf("-");

            }

            printf("\n");

        }

    }