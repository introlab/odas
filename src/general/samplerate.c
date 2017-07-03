    
    #include "samplerate.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    samplerate_obj * samplerate_construct_zero(void) {

        samplerate_obj * obj;

        obj = (samplerate_obj *) malloc(sizeof(samplerate_obj));

        obj->mu = 0;
        obj->sigma2 = 0.0f;

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    samplerate_obj * samplerate_clone(const samplerate_obj * obj) {

        samplerate_obj * clone;

        clone = (samplerate_obj *) malloc(sizeof(samplerate_obj));

        clone->mu = obj->mu;
        clone->sigma2 = obj->sigma2;

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void samplerate_destroy(samplerate_obj * obj) {

        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

    void samplerate_printf(const samplerate_obj * obj) {

        printf("mu = %u\n",obj->mu);
        printf("sigma2 = %f\n",obj->sigma2);

    }