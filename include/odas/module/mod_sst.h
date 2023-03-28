#ifndef __ODAS_MODULE_SST
#define __ODAS_MODULE_SST

   /**
    * \file     mod_sst.h
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
    #include <string.h>
    #include <math.h>

    #include "../general/mic.h"

    #include "../signal/coherence.h"
    #include "../signal/kalman.h"
    #include "../signal/mixture.h"
    #include "../signal/particle.h"

    #include "../system/kalman2kalman.h"
    #include "../system/particle2particle.h"
    #include "../system/kalman2coherence.h"
    #include "../system/particle2coherence.h"
    #include "../system/mixture2mixture.h"

    #include "../message/msg_pots.h"
    #include "../message/msg_targets.h"
    #include "../message/msg_tracks.h"
    #include "../module/mod_ssl.h"

    typedef struct mod_sst_obj {

        unsigned int nPots;
        unsigned int nTracksMax;
        unsigned int nTracks;
        unsigned int nTargetsMax;

        char mode;
        char add;

        mixture_obj ** mixtures;
        coherences_obj ** coherences;
        postprobs_obj ** postprobs;

        unsigned long long * ids;
        unsigned long long * idsAdded;
        unsigned long long * idsRemoved;
        char ** tags;
        
        char * type;

        kalman_obj ** kalmans;
        kalman2kalman_obj * kalman2kalman_prob;
        kalman2kalman_obj * kalman2kalman_active;
        kalman2kalman_obj * kalman2kalman_target;
        kalman2coherence_obj * kalman2coherence_prob;
        kalman2coherence_obj * kalman2coherence_active;
        kalman2coherence_obj * kalman2coherence_target;
        
        particles_obj ** particles;
        particle2particle_obj * particle2particle_prob;
        particle2particle_obj * particle2particle_active;
        particle2particle_obj * particle2particle_target;
        particle2coherence_obj * particle2coherence_prob;
        particle2coherence_obj * particle2coherence_active;
        particle2coherence_obj * particle2coherence_target;

        mixture2mixture_obj * mixture2mixture;
        
        float * sourceActivities;

        float theta_new;
        unsigned int N_prob;
        float theta_prob;
        unsigned int * N_inactive;
        float theta_inactive;

        unsigned int * n_prob;
        float * mean_prob;
        unsigned int * n_inactive;

        unsigned long long id;

        msg_pots_obj * in1;
        msg_targets_obj * in2;
        msg_tracks_obj * out;

        char enabled;

    } mod_sst_obj;

    typedef struct mod_sst_cfg {

        char mode;
        char add;

        unsigned int nTracksMax;
        unsigned int hopSize;
        
        float sigmaQ;
        
        unsigned int nParticles;
        float st_alpha;
        float st_beta;
        float st_ratio;
        float ve_alpha;
        float ve_beta;
        float ve_ratio;
        float ac_alpha;
        float ac_beta;
        float ac_ratio;
        float Nmin;

        float epsilon;
        float sigmaR_active;
        float sigmaR_prob;
        float sigmaR_target;
        gaussians_1d_obj * active_gmm;
        gaussians_1d_obj * inactive_gmm;
        float Pfalse;
        float Pnew;
        float Ptrack;

        float theta_new;
        unsigned int N_prob;
        float theta_prob;
        unsigned int * N_inactive;
        float theta_inactive;

    } mod_sst_cfg;

    mod_sst_obj * mod_sst_construct(const mod_sst_cfg * mod_sst_config, const mod_ssl_cfg * mod_ssl_config, const msg_pots_cfg * msg_pots_config, const msg_targets_cfg * msg_targets_config, const msg_tracks_cfg * msg_tracks_config);

    void mod_sst_destroy(mod_sst_obj * obj);

    int mod_sst_process(mod_sst_obj * obj);

    void mod_sst_connect(mod_sst_obj * obj, msg_pots_obj * in1, msg_targets_obj * in2, msg_tracks_obj * out);

    void mod_sst_disconnect(mod_sst_obj * obj);

    void mod_sst_enable(mod_sst_obj * obj);

    void mod_sst_disable(mod_sst_obj * obj);

    mod_sst_cfg * mod_sst_cfg_construct(void);

    void mod_sst_cfg_destroy(mod_sst_cfg * cfg);

    void mod_sst_cfg_printf(const mod_sst_cfg * cfg);

#endif