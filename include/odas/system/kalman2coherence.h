#ifndef __ODAS_SYSTEM_KALMAN2PRIOR
#define __ODAS_SYSTEM_KALMAN2PRIOR

   /**
    * \file     kalman2prior.h
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
