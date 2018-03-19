
   /**
    * \file     kalman2kalman.c
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

    #include <system/kalman2kalman.h>

    kalman2kalman_obj * kalman2kalman_construct(const float deltaT, const float sigmaQ, const float sigmaR, const float epsilon) {

        kalman2kalman_obj * obj;

        obj = (kalman2kalman_obj *) malloc(sizeof(kalman2kalman_obj));

        obj->deltaT = deltaT;
        obj->sigmaQ = sigmaQ;
        obj->sigmaR = sigmaR;
        obj->epsilon = epsilon;

        obj->F = matrix_construct_zero(6,6);
        obj->Ft = matrix_construct_zero(6,6);
        obj->Q = matrix_construct_zero(6,6);
        obj->H = matrix_construct_zero(3,6);
        obj->Ht = matrix_construct_zero(6,3);
        obj->R = matrix_construct_zero(3,3);

        obj->F->array[0*(obj->F->nCols)+0] = 1.0f;
        obj->F->array[0*(obj->F->nCols)+3] = deltaT;
        obj->F->array[1*(obj->F->nCols)+1] = 1.0f;
        obj->F->array[1*(obj->F->nCols)+4] = deltaT;
        obj->F->array[2*(obj->F->nCols)+2] = 1.0f;
        obj->F->array[2*(obj->F->nCols)+5] = deltaT;
        obj->F->array[3*(obj->F->nCols)+3] = 1.0f;
        obj->F->array[4*(obj->F->nCols)+4] = 1.0f;
        obj->F->array[5*(obj->F->nCols)+5] = 1.0f;

        obj->Ft->array[0*(obj->Ft->nCols)+0] = 1.0f;
        obj->Ft->array[3*(obj->Ft->nCols)+0] = deltaT;
        obj->Ft->array[1*(obj->Ft->nCols)+1] = 1.0f;
        obj->Ft->array[4*(obj->Ft->nCols)+1] = deltaT;
        obj->Ft->array[2*(obj->Ft->nCols)+2] = 1.0f;
        obj->Ft->array[5*(obj->Ft->nCols)+2] = deltaT;
        obj->Ft->array[3*(obj->Ft->nCols)+3] = 1.0f;
        obj->Ft->array[4*(obj->Ft->nCols)+4] = 1.0f;
        obj->Ft->array[5*(obj->Ft->nCols)+5] = 1.0f;

        obj->Q->array[3*(obj->Q->nCols)+3] = sigmaQ*sigmaQ;
        obj->Q->array[4*(obj->Q->nCols)+4] = sigmaQ*sigmaQ;
        obj->Q->array[5*(obj->Q->nCols)+5] = sigmaQ*sigmaQ;

        obj->H->array[0*(obj->H->nCols)+0] = 1.0f;
        obj->H->array[1*(obj->H->nCols)+1] = 1.0f;
        obj->H->array[2*(obj->H->nCols)+2] = 1.0f;

        obj->Ht->array[0*(obj->Ht->nCols)+0] = 1.0f;
        obj->Ht->array[1*(obj->Ht->nCols)+1] = 1.0f;
        obj->Ht->array[2*(obj->Ht->nCols)+2] = 1.0f;

        obj->R->array[0*(obj->R->nCols)+0] = sigmaR*sigmaR;
        obj->R->array[1*(obj->R->nCols)+1] = sigmaR*sigmaR;
        obj->R->array[2*(obj->R->nCols)+2] = sigmaR*sigmaR;

        obj->FP = matrix_construct_zero(6,6);
        obj->FPFt = matrix_construct_zero(6,6);

        obj->K = matrix_construct_zero(6,3);
        obj->PHt = matrix_construct_zero(6,3);
        obj->HP = matrix_construct_zero(3,6);
        obj->HPHt = matrix_construct_zero(3,3);
        obj->HPHt_R = matrix_construct_zero(3,3);
        obj->HPHt_Rinv = matrix_construct_zero(3,3);
        obj->Hx = matrix_construct_zero(3,1);
        obj->z = matrix_construct_zero(3,1);
        obj->z_Hx = matrix_construct_zero(3,1);
        obj->Kz_Hx = matrix_construct_zero(6,1);
        obj->pKz_Hx = matrix_construct_zero(6,1);
        obj->KHP = matrix_construct_zero(6,6);
        obj->pKHP = matrix_construct_zero(6,6);

        return obj;

    }

    void kalman2kalman_destroy(kalman2kalman_obj * obj) {

        matrix_destroy(obj->F);
        matrix_destroy(obj->Ft);
        matrix_destroy(obj->Q);
        matrix_destroy(obj->H);
        matrix_destroy(obj->Ht);
        matrix_destroy(obj->R);

        matrix_destroy(obj->FP);
        matrix_destroy(obj->FPFt);

        matrix_destroy(obj->K);
        matrix_destroy(obj->PHt);
        matrix_destroy(obj->HP);
        matrix_destroy(obj->HPHt);
        matrix_destroy(obj->HPHt_R);
        matrix_destroy(obj->HPHt_Rinv);
        matrix_destroy(obj->Hx);
        matrix_destroy(obj->z);
        matrix_destroy(obj->z_Hx);
        matrix_destroy(obj->Kz_Hx);
        matrix_destroy(obj->pKz_Hx);
        matrix_destroy(obj->KHP);
        matrix_destroy(obj->pKHP);

        free((void *) obj);

    }

    void kalman2kalman_init_pots(kalman2kalman_obj * obj, const pots_obj * pots, const unsigned int iPot, kalman_obj * kalman) {

        matrix_copy_zero(kalman->x_llm1);
        matrix_copy_zero(kalman->x_lm1lm1);
        matrix_copy_zero(kalman->P_llm1);
        matrix_copy_zero(kalman->P_lm1lm1);

        kalman->P_lm1lm1->array[0*(kalman->P_lm1lm1->nCols)+0] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[1*(kalman->P_lm1lm1->nCols)+1] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[2*(kalman->P_lm1lm1->nCols)+2] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[3*(kalman->P_lm1lm1->nCols)+3] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[4*(kalman->P_lm1lm1->nCols)+4] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[5*(kalman->P_lm1lm1->nCols)+5] = obj->sigmaQ * obj->sigmaQ;

        kalman->x_lm1lm1->array[0*(kalman->x_lm1lm1->nCols)+0] = pots->array[iPot * 4 + 0];
        kalman->x_lm1lm1->array[1*(kalman->x_lm1lm1->nCols)+0] = pots->array[iPot * 4 + 1];
        kalman->x_lm1lm1->array[2*(kalman->x_lm1lm1->nCols)+0] = pots->array[iPot * 4 + 2];

    }

    void kalman2kalman_init_targets(kalman2kalman_obj * obj, const targets_obj * targets, const unsigned int iTarget, kalman_obj * kalman) {

        matrix_copy_zero(kalman->x_llm1);
        matrix_copy_zero(kalman->x_lm1lm1);
        matrix_copy_zero(kalman->P_llm1);
        matrix_copy_zero(kalman->P_lm1lm1);

        kalman->P_lm1lm1->array[0*(kalman->P_lm1lm1->nCols)+0] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[1*(kalman->P_lm1lm1->nCols)+1] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[2*(kalman->P_lm1lm1->nCols)+2] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[3*(kalman->P_lm1lm1->nCols)+3] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[4*(kalman->P_lm1lm1->nCols)+4] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[5*(kalman->P_lm1lm1->nCols)+5] = obj->sigmaQ * obj->sigmaQ;

        kalman->x_lm1lm1->array[0*(kalman->x_lm1lm1->nCols)+0] = targets->array[iTarget * 3 + 0];
        kalman->x_lm1lm1->array[1*(kalman->x_lm1lm1->nCols)+0] = targets->array[iTarget * 3 + 1];
        kalman->x_lm1lm1->array[2*(kalman->x_lm1lm1->nCols)+0] = targets->array[iTarget * 3 + 2];

    }

    void kalman2kalman_predict(kalman2kalman_obj * obj, kalman_obj * kalman) {

        float xx, xy, xz;
        float vx, vy, vz;
        float norm, norm2, proj;

        matrix_mul(kalman->x_llm1, obj->F, kalman->x_lm1lm1);
        matrix_mul(obj->FP, obj->F, kalman->P_lm1lm1);
        matrix_mul(obj->FPFt, obj->FP, obj->Ft);
        matrix_add(kalman->P_llm1, obj->FPFt, obj->Q);

        xx = kalman->x_llm1->array[0*(kalman->x_llm1->nCols)+0];
        xy = kalman->x_llm1->array[1*(kalman->x_llm1->nCols)+0];
        xz = kalman->x_llm1->array[2*(kalman->x_llm1->nCols)+0];
        vx = kalman->x_llm1->array[3*(kalman->x_llm1->nCols)+0];
        vy = kalman->x_llm1->array[4*(kalman->x_llm1->nCols)+0];
        vz = kalman->x_llm1->array[5*(kalman->x_llm1->nCols)+0];

        norm2 = xx*xx + xy*xy + xz*xz;
        norm = sqrtf(norm2);
        proj = xx*vx + xy*vy + xz*vz;

        kalman->x_llm1->array[0*(kalman->x_llm1->nCols)+0] = xx / (norm + obj->epsilon);
        kalman->x_llm1->array[1*(kalman->x_llm1->nCols)+0] = xy / (norm + obj->epsilon);
        kalman->x_llm1->array[2*(kalman->x_llm1->nCols)+0] = xz / (norm + obj->epsilon);
        kalman->x_llm1->array[3*(kalman->x_llm1->nCols)+0] = vx - xx * proj / (norm2 + obj->epsilon);
        kalman->x_llm1->array[4*(kalman->x_llm1->nCols)+0] = vy - xy * proj / (norm2 + obj->epsilon);
        kalman->x_llm1->array[5*(kalman->x_llm1->nCols)+0] = vz - xz * proj / (norm2 + obj->epsilon);

    }

    void kalman2kalman_predict_static(kalman2kalman_obj * obj, kalman_obj * kalman) {

        matrix_copy_matrix(kalman->x_llm1, kalman->x_lm1lm1);
        matrix_copy_matrix(kalman->P_llm1, kalman->P_lm1lm1);

    }    

    void kalman2kalman_update(kalman2kalman_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, kalman_obj * kalman) {

        unsigned int iPot;
        float maxValue;
        unsigned int maxIndex;
        float updateFactor;
        
        // Find potential source with max prob

        maxValue = postprobs->arrayTrack[iTrack * postprobs->nPots];
        maxIndex = 0;

        for (iPot = 1; iPot < postprobs->nPots; iPot++) {

            if (maxValue < postprobs->arrayTrack[iTrack * postprobs->nPots + iPot]) {
                maxValue = postprobs->arrayTrack[iTrack * postprobs->nPots + iPot];
                maxIndex = iPot;
            }

        }

        obj->z->array[0*(obj->z->nCols)+0] = pots->array[maxIndex * 4 + 0];
        obj->z->array[1*(obj->z->nCols)+0] = pots->array[maxIndex * 4 + 1];
        obj->z->array[2*(obj->z->nCols)+0] = pots->array[maxIndex * 4 + 2];

        // Compute K
        matrix_mul(obj->HP, obj->H, kalman->P_llm1);
        matrix_mul(obj->HPHt, obj->HP, obj->Ht);
        matrix_add(obj->HPHt_R, obj->HPHt, obj->R);
        matrix_inv(obj->HPHt_Rinv, obj->HPHt_R);
        matrix_mul(obj->PHt, kalman->P_llm1, obj->Ht);
        matrix_mul(obj->K, obj->PHt, obj->HPHt_Rinv);

        updateFactor = postprobs->arrayTrackTotal[iTrack];

        // Update x
        matrix_mul(obj->Hx, obj->H, kalman->x_llm1);
        matrix_sub(obj->z_Hx, obj->z, obj->Hx);
        matrix_mul(obj->Kz_Hx, obj->K, obj->z_Hx);
        matrix_scale(obj->pKz_Hx, obj->Kz_Hx, updateFactor);
        matrix_add(kalman->x_lm1lm1, kalman->x_llm1, obj->pKz_Hx);

        // Update P
        matrix_mul(obj->KHP, obj->K, obj->HP);
        matrix_scale(obj->pKHP, obj->KHP, updateFactor);
        matrix_sub(kalman->P_lm1lm1, kalman->P_llm1, obj->pKHP);

    }

    void kalman2kalman_update_static(kalman2kalman_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, kalman_obj * kalman) {

        matrix_copy_matrix(kalman->x_lm1lm1, kalman->x_llm1);
        matrix_copy_matrix(kalman->P_lm1lm1, kalman->P_llm1);

    }

    void kalman2kalman_estimate(kalman2kalman_obj * obj, const kalman_obj * kalman, float * x, float * y, float * z) {

        *x = kalman->x_lm1lm1->array[0*(kalman->x_lm1lm1->nCols)+0];
        *y = kalman->x_lm1lm1->array[1*(kalman->x_lm1lm1->nCols)+0];
        *z = kalman->x_lm1lm1->array[2*(kalman->x_lm1lm1->nCols)+0];

    }
