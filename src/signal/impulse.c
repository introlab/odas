    
    #include "impulse.h"

    impulse_obj * impulse_construct(const unsigned int nCoefficients) {

        impulse_obj * obj;

        obj = (impulse_obj *) malloc(sizeof(impulse_obj));

        obj->nCoefficients = nCoefficients;
        obj->array = (float *) malloc(sizeof(float) * nCoefficients);
        memset(obj->array, 0x00, sizeof(float) * nCoefficients);

        return obj;

    }

    void impulse_destroy(impulse_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }