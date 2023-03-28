#ifndef __ODAS_SYSTEM_PARTICLE2PARTICLE
#define __ODAS_SYSTEM_PARTICLE2PARTICLE

   /**
    * \file     particle2particle.h
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

    #include <utils/gaussian.h>
    #include <utils/random.h>
    #include <signal/particle.h>
    #include <signal/postprob.h>
    #include <signal/pot.h>
    #include <signal/target.h>

    typedef struct particle2particle_obj {

        unsigned int nParticles;
        float deltaT;

        float alphas[3];
        float betas[3];
        float as[3];
        float bs[3];
        float ratios[3];

        float sigmaR;
        float expScale;
        float expFactor;

        float * pdf_ratio;
        unsigned int * indexes_ratio;
        random_obj * rnd_ratio;
        
        float * pdf_weight;
        unsigned int * indexes_weight;
        random_obj * rnd_weight;

        float * realisation_normal;
        double epsilon;
        normaloff_obj * normaloff;

        float * sum_P_p_x_O;
        particles_obj * particles;

        float Nmin;

    } particle2particle_obj;
                  
    particle2particle_obj * particle2particle_construct(const unsigned int nParticles, const float deltaT, const float st_alpha, const float st_beta, const float st_ratio, const float ve_alpha, const float ve_beta, const float ve_ratio, const float ac_alpha, const float ac_beta, const float ac_ratio, const double epsilon, const float sigmaR, const float Nmin);

    void particle2particle_destroy(particle2particle_obj * obj);

    void particle2particle_init_pots(particle2particle_obj * obj, const pots_obj * pots, const unsigned int iPot, particles_obj * particles);

    void particle2particle_init_targets(particle2particle_obj * obj, const targets_obj * targets, const unsigned int iTarget, particles_obj * particles);

    void particle2particle_predict(particle2particle_obj * obj, particles_obj * particles);

    void particle2particle_predict_static(particle2particle_obj * obj, particles_obj * particles);

    void particle2particle_update(particle2particle_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, particles_obj * particles);

    void particle2particle_update_static(particle2particle_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, particles_obj * particles);

    void particle2particle_estimate(const particle2particle_obj * obj, const particles_obj * particles, float * x, float * y, float * z);

#endif
