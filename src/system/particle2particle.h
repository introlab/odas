#ifndef __ODAS_SYSTEM_PARTICLE2PARTICLE
#define __ODAS_SYSTEM_PARTICLE2PARTICLE

    #include "../utils/gaussian.h"
    #include "../utils/random.h"
    #include "../signal/particle.h"
    #include "../signal/postprob.h"
    #include "../signal/pot.h"

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

    void particle2particle_init(particle2particle_obj * obj, const pots_obj * pots, const unsigned int iPot, particles_obj * particles);

    void particle2particle_predict(particle2particle_obj * obj, particles_obj * particles);

    void particle2particle_update(particle2particle_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, particles_obj * particles);

    void particle2particle_estimate(const particle2particle_obj * obj, const particles_obj * particles, float * x, float * y, float * z);

#endif