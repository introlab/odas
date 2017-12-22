
    #include "pair.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    pairs_obj * pairs_construct_zero(const unsigned int nPairs) {

        pairs_obj * obj;

        obj = (pairs_obj *) malloc(sizeof(pairs_obj));

        obj->nPairs = nPairs;
        obj->array = (char *) malloc(sizeof(char) * nPairs);
        memset(obj->array, 0x00, sizeof(char) * nPairs);

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    pairs_obj * pairs_clone(const pairs_obj * obj) {

        pairs_obj * clone;

        clone = (pairs_obj *) malloc(sizeof(pairs_obj));

        clone->nPairs = obj->nPairs;
        clone->array = (char *) malloc(sizeof(char) * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(char) * obj->nPairs);        

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destroy                                                  |
    // +----------------------------------------------------------+

    void pairs_destroy(pairs_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+    

    void pairs_printf(const pairs_obj * obj) {

        unsigned int iPair;

        printf("nPairs: %u\n", obj->nPairs);
        
        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            printf("(%02u): %d\n", iPair, obj->array[iPair]);    
        }

    }