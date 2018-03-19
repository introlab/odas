#ifndef __ODAS_SYSTEM_KALMAN2KALMAN
#define __ODAS_SYSTEM_KALMAN2KALMAN

   /**
    * \file     kalman2kalman.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
