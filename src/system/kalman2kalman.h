#ifndef __ODAS_SYSTEM_KALMAN2KALMAN
#define __ODAS_SYSTEM_KALMAN2KALMAN

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/postprob.h"
    #include "../signal/kalman.h"
    #include "../signal/pot.h"
    #include "../utils/matrix.h"

    typedef struct kalman2kalman_obj {

        float epsilon;

        float deltaT;
        float sigmaQ;
        float sigmaR;

        matrix_obj * F;
        matrix_obj * Ft;
        matrix_obj * Q;
        matrix_obj * H;
        matrix_obj * Ht;
        matrix_obj * R;

        matrix_obj * FP;
        matrix_obj * FPFt;
        
        matrix_obj * K;
        matrix_obj * PHt;
        matrix_obj * HP;
        matrix_obj * HPHt;
        matrix_obj * HPHt_R;
        matrix_obj * HPHt_Rinv;
        matrix_obj * Hx;
        matrix_obj * z;
        matrix_obj * z_Hx;
        matrix_obj * Kz_Hx;
        matrix_obj * pKz_Hx;
        matrix_obj * KHP;
        matrix_obj * pKHP;

    } kalman2kalman_obj;

    kalman2kalman_obj * kalman2kalman_construct(const float deltaT, const float sigmaQ, const float sigmaR, const float epsilon);

    void kalman2kalman_destroy(kalman2kalman_obj * obj);

    void kalman2kalman_init(kalman2kalman_obj * obj, const pots_obj * pots, const unsigned int iPot, kalman_obj * kalman);

    void kalman2kalman_predict(kalman2kalman_obj * obj, kalman_obj * kalman);

    void kalman2kalman_update(kalman2kalman_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, kalman_obj * kalman);

    void kalman2kalman_estimate(kalman2kalman_obj * obj, const kalman_obj * kalman, float * x, float * y, float * z);

#endif