    
    #include "soundspeed.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    soundspeed_obj * soundspeed_construct_zero(void) {

        soundspeed_obj * obj;

        obj = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        obj->mu = 0.0f;
        obj->sigma2 = 0.0f;

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    soundspeed_obj * soundspeed_clone(const soundspeed_obj * obj) {

        soundspeed_obj * clone;

        clone = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        clone->mu = obj->mu;
        clone->sigma2 = obj->sigma2;

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void soundspeed_destroy(soundspeed_obj * obj) {

        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

    void soundspeed_printf(const soundspeed_obj * obj) {

        printf("mu = %f\n",obj->mu);
        printf("sigma2 = %f\n",obj->sigma2);

    }