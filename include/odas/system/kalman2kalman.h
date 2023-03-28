#ifndef __ODAS_SYSTEM_KALMAN2KALMAN
#define __ODAS_SYSTEM_KALMAN2KALMAN

   /**
    * \file     kalman2kalman.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    #include <signal/postprob.h>
    #include <signal/kalman.h>
    #include <signal/pot.h>
    #include <signal/target.h>
    #include <utils/matrix.h>

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

    void kalman2kalman_init_pots(kalman2kalman_obj * obj, const pots_obj * pots, const unsigned int iPot, kalman_obj * kalman);

    void kalman2kalman_init_targets(kalman2kalman_obj * obj, const targets_obj * targets, const unsigned int iTarget, kalman_obj * kalman);

    void kalman2kalman_predict(kalman2kalman_obj * obj, kalman_obj * kalman);

    void kalman2kalman_predict_static(kalman2kalman_obj * obj, kalman_obj * kalman);

    void kalman2kalman_update(kalman2kalman_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, kalman_obj * kalman);

    void kalman2kalman_update_static(kalman2kalman_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, kalman_obj * kalman);    

    void kalman2kalman_estimate(kalman2kalman_obj * obj, const kalman_obj * kalman, float * x, float * y, float * z);

#endif
