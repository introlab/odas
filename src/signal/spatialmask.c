    
    #include "spatialmask.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    spatialmasks_obj * spatialmasks_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        spatialmasks_obj * obj;

        obj = (spatialmasks_obj *) malloc(sizeof(spatialmasks_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->array = (char *) malloc(sizeof(char) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(char) * nPoints * nPairs);

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    spatialmasks_obj * spatialmasks_clone(const spatialmasks_obj * obj) {

        spatialmasks_obj * clone;

        clone = (spatialmasks_obj *) malloc(sizeof(spatialmasks_obj));

        clone->nPoints = obj->nPoints;
        clone->nPairs = obj->nPairs;

        clone->array = (char *) malloc(sizeof(char) * obj->nPoints * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(char) * obj->nPoints * obj->nPairs);

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void spatialmasks_destroy(spatialmasks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

    void spatialmasks_printf(const spatialmasks_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                if (obj->array[iPoint * obj->nPairs + iPair] != 0x00) {

                    printf("1");

                }
                else {

                    printf("0");

                }

            }

            printf("\n");            

        }

    }