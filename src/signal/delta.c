
    #include "delta.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    deltas_obj * deltas_construct_zero(const unsigned int nPairs) {

        deltas_obj * obj;

        obj = (deltas_obj *) malloc(sizeof(deltas_obj));

        obj->nPairs = nPairs;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPairs);

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    deltas_obj * deltas_clone(const deltas_obj * obj) {

        deltas_obj * clone;

        clone = (deltas_obj *) malloc(sizeof(deltas_obj));

        clone->nPairs = obj->nPairs;
        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nPairs);

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void deltas_destroy(deltas_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

    void deltas_printf(const deltas_obj * obj) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("(%02u): %02u\n",iPair,obj->array[iPair]);

        }

    }