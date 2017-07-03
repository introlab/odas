#ifndef __ODAS_SIGNAL_KALMAN
#define __ODAS_SIGNAL_KALMAN

    #include <stdlib.h>
    #include <stdio.h>

    #include "../utils/matrix.h"

    typedef struct kalman_obj {

        matrix_obj * x_lm1lm1;
        matrix_obj * x_llm1;
        matrix_obj * P_lm1lm1;
        matrix_obj * P_llm1;

    } kalman_obj;

    kalman_obj * kalman_construct_zero(void);

    void kalman_destroy(kalman_obj * obj);

#endif