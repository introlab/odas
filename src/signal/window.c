
    #include "window.h"

    window_obj * window_construct_zero(const unsigned int frameSize) {

        window_obj * obj;

        obj = (window_obj *) malloc(sizeof(window_obj));

        obj->frameSize = frameSize;
        obj->array = (float *) malloc(sizeof(float) * frameSize);
        memset(obj->array, frameSize, sizeof(float));

        return obj;

    }

    void window_destroy(window_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }