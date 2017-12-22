
    #include "spatialindex.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    spatialindexes_obj * spatialindexes_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        spatialindexes_obj * obj;

        obj = (spatialindexes_obj *) malloc(sizeof(spatialindexes_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;
        
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPoints * nPairs);

        obj->count = (unsigned int *) malloc(sizeof(unsigned int) * nPoints);
        memset(obj->count, 0x00, sizeof(unsigned int) * nPoints);

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    spatialindexes_obj * spatialindexes_clone(const spatialindexes_obj * obj) {

        spatialindexes_obj * clone;

        clone = (spatialindexes_obj *) malloc(sizeof(spatialindexes_obj));

        clone->nPoints = obj->nPoints;
        clone->nPairs = obj->nPairs;

        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPoints * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nPoints * obj->nPairs);

        clone->count = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPoints);
        memcpy(clone->count, obj->count, sizeof(unsigned int) * obj->nPoints);

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+    

    void spatialindexes_destroy(spatialindexes_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->count);

        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

    void spatialindexes_printf(const spatialindexes_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            if (obj->count[iPoint] > 0) {

                for (iPair = 0; iPair < obj->count[iPoint]; iPair++) {

                    printf("%03u ",obj->array[iPoint * obj->nPairs + iPair]);

                }

            }
            else {

                printf("-");

            }

            printf("\n");

        }

    }