#ifndef __ODAS_SYSTEM_KALMAN2PRIOR
#define __ODAS_SYSTEM_KALMAN2PRIOR

    #include <stdlib.h>
    #include <math.h>

    #include "../signal/coherence.h"
    #include "../signal/kalman.h"
    #include "../signal/pot.h"
    #include "../utils/matrix.h"

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