
    #include "kalman.h"
    
    kalman_obj * kalman_construct_zero(void) {

        kalman_obj * obj;

        obj = (kalman_obj *) malloc(sizeof(kalman_obj));

        obj->x_lm1lm1 = matrix_construct_zero(6,1);
        obj->x_llm1 = matrix_construct_zero(6,1);
        obj->P_lm1lm1 = matrix_construct_zero(6,6);
        obj->P_llm1 = matrix_construct_zero(6,6);

        return obj;

    }

    void kalman_destroy(kalman_obj * obj) {

        matrix_destroy(obj->x_lm1lm1);
        matrix_destroy(obj->x_llm1);
        matrix_destroy(obj->P_lm1lm1);
        matrix_destroy(obj->P_llm1);

        free((void *) obj);

    }
