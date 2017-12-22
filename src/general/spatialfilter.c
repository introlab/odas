    
    #include "spatialfilter.h"

    spatialfilter_obj * spatialfilter_construct_zero(void) {

        spatialfilter_obj * obj;

        obj = (spatialfilter_obj *) malloc(sizeof(spatialfilter_obj));

        obj->direction = (float *) malloc(sizeof(float) * 3);
        memset(obj->direction, 0x00, sizeof(float) * 3);

        obj->thetaAllPass = 0.0f;
        obj->thetaNoPass = 0.0f;

        return obj;

    }

    spatialfilter_obj * spatialfilter_clone(const spatialfilter_obj * obj) {

        spatialfilter_obj * clone;

        clone = (spatialfilter_obj *) malloc(sizeof(spatialfilter_obj));

        clone->direction = (float *) malloc(sizeof(float) * 3);
        memcpy(clone->direction, obj->direction, sizeof(float) * 3);

        clone->thetaAllPass = obj->thetaAllPass;
        clone->thetaNoPass = obj->thetaNoPass;

        return clone;

    }

    void spatialfilter_destroy(spatialfilter_obj * obj) {

        free((void *) obj->direction);
        free((void *) obj);

    }

    void spatialfilter_printf(const spatialfilter_obj * obj) {

        printf("direction = (%+1.3f,%+1.3f,%+1.3f)\n", obj->direction[0], obj->direction[1], obj->direction[2]);
        printf("thetaAllPass = %f\n", obj->thetaAllPass);
        printf("thetaNoPass = %f\n", obj->thetaNoPass);

    }
