#ifndef __ODAS_SYSTEM_KALMAN2PRIOR
#define __ODAS_SYSTEM_KALMAN2PRIOR

   /**
    * \file     kalman2prior.h
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
    #include <math.h>

    #include <signal/coherence.h>
    #include <signal/kalman.h>
    #include <signal/pot.h>
    #include <utils/matrix.h>

    typedef struct kalman2coherence_obj {

        float epsilon;

        matrix_obj * H;
        matrix_obj * Ht;

        matrix_obj * mu_t;
        matrix_obj * mu_t_t;
        matrix_obj * mu_s;
        matrix_obj * mu_s_t;
        matrix_obj * mu_st;
        matrix_obj * mu_st_t;

        matrix_obj * HP;
        matrix_obj * sigma_epsilon;

        matrix_obj * sigma_t;
        matrix_obj * sigma_s;
        matrix_obj * sigma_st;
        
        matrix_obj * sigma_t_epsilon;
        matrix_obj * sigma_t_inv;
        matrix_obj * sigma_s_inv;
        matrix_obj * sigma_st_inv;

        matrix_obj * sigma_t_inv_mu_t;
        matrix_obj * sigma_s_inv_mu_s;
        matrix_obj * sigma_st_inv_mu_st;

        matrix_obj * mu_t_t_sigma_t_inv_mu_t;
        matrix_obj * mu_s_t_sigma_s_inv_mu_s;
        matrix_obj * mu_st_t_sigma_st_inv_mu_st;

        matrix_obj * sigma_t_inv_mu_t_sigma_s_inv_mu_s;

    } kalman2coherence_obj;

    kalman2coherence_obj * kalman2coherence_construct(const float epsilon, const float sigmaR);

    void kalman2coherence_destroy(kalman2coherence_obj * obj);

    void kalman2coherence_process(kalman2coherence_obj * obj, const kalman_obj * kalman, const pots_obj * pots, const unsigned int iTrack, coherences_obj * coherences);


#endif
