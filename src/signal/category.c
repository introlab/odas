    
    #include "category.h"

    categories_obj * categories_construct_zero(const unsigned int nSignals) {

        categories_obj * obj;

        obj = (categories_obj *) malloc(sizeof(categories_obj));

        obj->nSignals = nSignals;
        obj->array = (char *) malloc(sizeof(char) * nSignals);
        memset(obj->array, 0x00, sizeof(char) * nSignals);

        return obj;

    }

    void categories_destroy(categories_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void categories_copy(categories_obj * dest, const categories_obj * src) {

        memcpy(dest->array, src->array, sizeof(char) * src->nSignals);

    }

    void categories_zero(categories_obj * obj) {

        memset(obj->array, 0x00, sizeof(char) * obj->nSignals);

    }

    void categories_printf(const categories_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %c\n",iSignal,obj->array[iSignal]);

        }

    }