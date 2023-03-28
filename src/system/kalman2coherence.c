
   /**
    * \file     kalman2coherence.c
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

    #include <system/kalman2coherence.h>

    kalman2coherence_obj * kalman2coherence_construct(const float epsilon, const float sigmaR) {

        kalman2coherence_obj * obj;

        obj = (kalman2coherence_obj *) malloc(sizeof(kalman2coherence_obj));

        obj->epsilon = epsilon;

        obj->H = matrix_construct_zero(3,6);
        obj->H->array[0*obj->H->nCols+0] = 1.0f;
        obj->H->array[1*obj->H->nCols+1] = 1.0f;
        obj->H->array[2*obj->H->nCols+2] = 1.0f;
        
        obj->Ht = matrix_construct_zero(6,3);
        obj->Ht->array[0*obj->Ht->nCols+0] = 1.0f;
        obj->Ht->array[1*obj->Ht->nCols+1] = 1.0f;
        obj->Ht->array[2*obj->Ht->nCols+2] = 1.0f;

        obj->mu_t = matrix_construct_zero(3,1);
        obj->mu_t_t = matrix_construct_zero(1,3);
        obj->mu_s = matrix_construct_zero(3,1);
        obj->mu_s_t = matrix_construct_zero(1,3);
        obj->mu_st = matrix_construct_zero(3,1);
        obj->mu_st_t = matrix_construct_zero(1,3);

        obj->HP = matrix_construct_zero(3,6);
        obj->sigma_epsilon = matrix_construct_zero(3,3);

        obj->sigma_t = matrix_construct_zero(3,3);
        obj->sigma_s = matrix_construct_zero(3,3);
        obj->sigma_st = matrix_construct_zero(3,3);
        
        obj->sigma_t_epsilon = matrix_construct_zero(3,3);
        obj->sigma_t_inv = matrix_construct_zero(3,3);
        obj->sigma_s_inv = matrix_construct_zero(3,3);
        obj->sigma_st_inv = matrix_construct_zero(3,3);    

        obj->sigma_t_inv_mu_t = matrix_construct_zero(3,1);
        obj->sigma_s_inv_mu_s = matrix_construct_zero(3,1);
        obj->sigma_st_inv_mu_st = matrix_construct_zero(3,1);

        obj->mu_t_t_sigma_t_inv_mu_t = matrix_construct_zero(1,1);
        obj->mu_s_t_sigma_s_inv_mu_s = matrix_construct_zero(1,1);
        obj->mu_st_t_sigma_st_inv_mu_st = matrix_construct_zero(1,1);
        
        obj->sigma_t_inv_mu_t_sigma_s_inv_mu_s = matrix_construct_zero(3,1);

        obj->sigma_s->array[0*obj->sigma_s->nCols+0] = sigmaR*sigmaR;
        obj->sigma_s->array[1*obj->sigma_s->nCols+1] = sigmaR*sigmaR;
        obj->sigma_s->array[2*obj->sigma_s->nCols+2] = sigmaR*sigmaR;

        obj->sigma_epsilon->array[0*obj->sigma_epsilon->nCols+0] = epsilon;
        obj->sigma_epsilon->array[1*obj->sigma_epsilon->nCols+1] = epsilon;
        obj->sigma_epsilon->array[2*obj->sigma_epsilon->nCols+2] = epsilon;

        matrix_inv(obj->sigma_s_inv, obj->sigma_s);

        return obj;

    }

    void kalman2coherence_destroy(kalman2coherence_obj * obj) {

        matrix_destroy(obj->H);
        matrix_destroy(obj->Ht);
        
        matrix_destroy(obj->mu_t);
        matrix_destroy(obj->mu_t_t);
        matrix_destroy(obj->mu_s);
        matrix_destroy(obj->mu_s_t);
        matrix_destroy(obj->mu_st);
        matrix_destroy(obj->mu_st_t);

        matrix_destroy(obj->HP);
        matrix_destroy(obj->sigma_epsilon);

        matrix_destroy(obj->sigma_t);
        matrix_destroy(obj->sigma_s);
        matrix_destroy(obj->sigma_st);

        matrix_destroy(obj->sigma_t_epsilon);
        matrix_destroy(obj->sigma_t_inv);
        matrix_destroy(obj->sigma_s_inv);
        matrix_destroy(obj->sigma_st_inv);

        matrix_destroy(obj->sigma_t_inv_mu_t);
        matrix_destroy(obj->sigma_s_inv_mu_s);
        matrix_destroy(obj->sigma_st_inv_mu_st);

        matrix_destroy(obj->mu_t_t_sigma_t_inv_mu_t);
        matrix_destroy(obj->mu_s_t_sigma_s_inv_mu_s);
        matrix_destroy(obj->mu_st_t_sigma_st_inv_mu_st);

        matrix_destroy(obj->sigma_t_inv_mu_t_sigma_s_inv_mu_s);

        free((void *) obj);

    }

    void kalman2coherence_process(kalman2coherence_obj * obj, const kalman_obj * kalman, const pots_obj * pots, const unsigned int iTrack, coherences_obj * coherences) {

        unsigned int iPot;
        float B1, B2, B3, B4;
        float weight;

        // Compute mu_t
        matrix_mul(obj->mu_t, obj->H, kalman->x_llm1);
        matrix_transpose(obj->mu_t_t, obj->mu_t);        

        // Compute sigma_t
        matrix_mul(obj->HP, obj->H, kalman->P_llm1);
        matrix_mul(obj->sigma_t, obj->HP, obj->Ht);
        matrix_add(obj->sigma_t_epsilon, obj->sigma_t, obj->sigma_epsilon);

        // Compute sigma_t^-1
        matrix_inv(obj->sigma_t_inv, obj->sigma_t_epsilon);

        // Compute sigma_t^-1 * mu_t
        matrix_mul(obj->sigma_t_inv_mu_t, obj->sigma_t_inv, obj->mu_t);

        // Compute B3
        matrix_mul(obj->mu_t_t_sigma_t_inv_mu_t, obj->mu_t_t, obj->sigma_t_inv_mu_t);
        B3 = obj->mu_t_t_sigma_t_inv_mu_t->array[0*(obj->mu_t_t_sigma_t_inv_mu_t->nCols)+0];

        for (iPot = 0; iPot < pots->nPots; iPot++) {

            // Compute mu_s
            obj->mu_s->array[0*(obj->mu_s->nCols)+0] = pots->array[iPot*4+0];
            obj->mu_s->array[1*(obj->mu_s->nCols)+0] = pots->array[iPot*4+1];
            obj->mu_s->array[2*(obj->mu_s->nCols)+0] = pots->array[iPot*4+2];
            matrix_transpose(obj->mu_s_t, obj->mu_s);    
           
            // Compute sigma_st^-1
            matrix_add(obj->sigma_st_inv, obj->sigma_s_inv, obj->sigma_t_inv);

            // Compute sigma_st
            matrix_inv(obj->sigma_st, obj->sigma_st_inv);

            // Compute sigma_s^-1 * mu_s
            matrix_mul(obj->sigma_s_inv_mu_s, obj->sigma_s_inv, obj->mu_s);

            // Compute (sigma_t^-1 * mu_t + sigma_s^-1 * mu_s)
            matrix_add(obj->sigma_t_inv_mu_t_sigma_s_inv_mu_s, obj->sigma_t_inv_mu_t, obj->sigma_s_inv_mu_s);

            // Compute mu_st = sigma_st * (sigma_t^-1 * mu_t + sigma_s^-1 * mu_s)
            matrix_mul(obj->mu_st, obj->sigma_st, obj->sigma_t_inv_mu_t_sigma_s_inv_mu_s);
            matrix_transpose(obj->mu_st_t, obj->mu_st);     

            // Compute B1
            B1 = logf(matrix_det(obj->sigma_st)) - logf(8.0f * M_PI * M_PI * M_PI * matrix_det(obj->sigma_t) * matrix_det(obj->sigma_s));

            // Compute B2
            matrix_mul(obj->sigma_st_inv_mu_st, obj->sigma_st_inv, obj->mu_st);
            matrix_mul(obj->mu_st_t_sigma_st_inv_mu_st, obj->mu_st_t, obj->sigma_st_inv_mu_st);
            B2 = obj->mu_st_t_sigma_st_inv_mu_st->array[0*(obj->mu_st_t_sigma_st_inv_mu_st->nCols)+0];

            // Compute B4
            matrix_mul(obj->mu_s_t_sigma_s_inv_mu_s, obj->mu_s_t, obj->sigma_s_inv_mu_s);
            B4 = obj->mu_s_t_sigma_s_inv_mu_s->array[0*(obj->mu_s_t_sigma_s_inv_mu_s->nCols)+0];

            // Compute weight
            weight = expf(0.5f * (B1+B2-B3-B4));

            coherences->array[iTrack * pots->nPots + iPot] = weight;

        }

    }
