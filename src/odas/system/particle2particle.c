
   /**
    * \file     particle2particle.c
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
    
    #include <system/particle2particle.h>

    particle2particle_obj * particle2particle_construct(const unsigned int nParticles, const float deltaT, const float st_alpha, const float st_beta, const float st_ratio, const float ve_alpha, const float ve_beta, const float ve_ratio, const float ac_alpha, const float ac_beta, const float ac_ratio, const double epsilon, const float sigmaR, const float Nmin) {

        particle2particle_obj * obj;
        unsigned int iState;

        obj = (particle2particle_obj *) malloc(sizeof(particle2particle_obj));

        obj->nParticles = nParticles;
        obj->deltaT = deltaT;

        obj->alphas[0] = st_alpha;
        obj->alphas[1] = ve_alpha;
        obj->alphas[2] = ac_alpha;
        obj->betas[0] = st_beta;
        obj->betas[1] = ve_beta;
        obj->betas[2] = ac_beta;
        obj->ratios[0] = st_ratio;
        obj->ratios[1] = ve_ratio;
        obj->ratios[2] = ac_ratio;

        for (iState = 0; iState < 3; iState++) {

            obj->as[iState] = expf(-1.0f * obj->alphas[iState] * deltaT);
            obj->bs[iState] = obj->betas[iState] * sqrtf(1.0f - obj->as[iState] * obj->as[iState]);

        }

        obj->rnd_ratio = random_construct_zero(3);
        random_pdf(obj->rnd_ratio, obj->ratios);
        obj->indexes_ratio = (unsigned int *) malloc(sizeof(unsigned int) * nParticles);

        obj->pdf_weight = (float *) malloc(sizeof(float) * nParticles);
        obj->indexes_weight = (unsigned int *) malloc(sizeof(unsigned int) * nParticles);
        obj->rnd_weight = random_construct_zero(nParticles);

        obj->realisation_normal = (float *) malloc(sizeof(float) * nParticles * 3);
        obj->normaloff = normaloff_construct_rnd(epsilon, 10000);

        obj->epsilon = epsilon;
        obj->Nmin = Nmin;

        obj->sigmaR = sigmaR;
        obj->expScale = 1.0f / (sigmaR*sigmaR*sigmaR * powf(2*M_PI,(3.0f/2.0f)));
        obj->expFactor = -1.0f / (2.0f * obj->sigmaR * obj->sigmaR);

        obj->sum_P_p_x_O = (float *) malloc(sizeof(float) * nParticles);
        obj->particles = particles_construct_zero(nParticles);

        return obj;

    }

    void particle2particle_destroy(particle2particle_obj * obj) {

        random_destroy(obj->rnd_ratio);
        free((void *) obj->indexes_ratio);

        free((void *) obj->pdf_weight);
        free((void *) obj->indexes_weight);
        random_destroy(obj->rnd_weight);

        free((void *) obj->realisation_normal);
        normaloff_destroy(obj->normaloff);

        free((void *) obj->sum_P_p_x_O);
        particles_destroy(obj->particles);

        free((void *) obj);

    }

    void particle2particle_init_pots(particle2particle_obj * obj, const pots_obj * pots, const unsigned int iPot, particles_obj * particles) {

        unsigned int iParticle;

        random_generate(obj->rnd_ratio, obj->nParticles, obj->indexes_ratio);        

        memset(particles->array, 0x00, sizeof(float) * 7 * obj->nParticles);

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            particles->array[iParticle * 7 + 0] = pots->array[iPot * 4 + 0];
            particles->array[iParticle * 7 + 1] = pots->array[iPot * 4 + 1];
            particles->array[iParticle * 7 + 2] = pots->array[iPot * 4 + 2];
            particles->array[iParticle * 7 + 6] = (1.0f / ((float) obj->nParticles));

            particles->state[iParticle] = (unsigned char) (obj->indexes_ratio[iParticle]);

        }

    }

    void particle2particle_init_targets(particle2particle_obj * obj, const targets_obj * targets, const unsigned int iTarget, particles_obj * particles) {

        unsigned int iParticle;

        random_generate(obj->rnd_ratio, obj->nParticles, obj->indexes_ratio);        

        memset(particles->array, 0x00, sizeof(float) * 7 * obj->nParticles);

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            particles->array[iParticle * 7 + 0] = targets->array[iTarget * 3 + 0];
            particles->array[iParticle * 7 + 1] = targets->array[iTarget * 3 + 1];
            particles->array[iParticle * 7 + 2] = targets->array[iTarget * 3 + 2];
            particles->array[iParticle * 7 + 6] = (1.0f / ((float) obj->nParticles));

            particles->state[iParticle] = (unsigned char) (obj->indexes_ratio[iParticle]);

        }        

    }

    void particle2particle_predict(particle2particle_obj * obj, particles_obj * particles) {

        unsigned int iParticle;
        float a, b;

        normaloff_generate(obj->normaloff, obj->nParticles * 3, obj->realisation_normal);

        for (iParticle = 0; iParticle < particles->nParticles; iParticle++) {

            a = obj->as[particles->state[iParticle]];
            b = obj->bs[particles->state[iParticle]];

            particles->array[iParticle * 7 + 3] = a * particles->array[iParticle * 7 + 3] + b * obj->realisation_normal[iParticle * 3 + 0];
            particles->array[iParticle * 7 + 4] = a * particles->array[iParticle * 7 + 4] + b * obj->realisation_normal[iParticle * 3 + 1];
            particles->array[iParticle * 7 + 5] = a * particles->array[iParticle * 7 + 5] + b * obj->realisation_normal[iParticle * 3 + 2];
            
            particles->array[iParticle * 7 + 0] = particles->array[iParticle * 7 + 0] + obj->deltaT * particles->array[iParticle * 7 + 3];
            particles->array[iParticle * 7 + 1] = particles->array[iParticle * 7 + 1] + obj->deltaT * particles->array[iParticle * 7 + 4];
            particles->array[iParticle * 7 + 2] = particles->array[iParticle * 7 + 2] + obj->deltaT * particles->array[iParticle * 7 + 5];
            
        }

    }

    void particle2particle_predict_static(particle2particle_obj * obj, particles_obj * particles) {

        // Do nothing: keep old particles distribution

    }

    void particle2particle_update(particle2particle_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, particles_obj * particles) {

        unsigned int iParticle;
        unsigned int iPot;
        float x1, y1, z1;
        float x2, y2, z2;
        float dx, dy, dz;
        float scale, factor;   
        float postprob;
        float expr, value;    
        float uniform, alpha, oneminusalpha, alphanorm;
        float p_x_O;

        float total_sum_P_p_x_O;
        float total_w;

        float Neff;

        // Compute sum{P_q,j * p(O_q|x_j,i)}, and normalize

        memset(obj->sum_P_p_x_O, 0x00, sizeof(float) * obj->nParticles);

        total_sum_P_p_x_O = obj->epsilon;
        scale = obj->expScale;
        factor = obj->expFactor;

        for (iPot = 0; iPot < pots->nPots; iPot++) {

            x1 = pots->array[iPot * 4 + 0];
            y1 = pots->array[iPot * 4 + 1];
            z1 = pots->array[iPot * 4 + 2];

            postprob = postprobs->arrayTrack[iTrack * pots->nPots + iPot];

            for (iParticle = 0; iParticle < particles->nParticles; iParticle++) {

                x2 = particles->array[iParticle * 7 + 0];
                y2 = particles->array[iParticle * 7 + 1];
                z2 = particles->array[iParticle * 7 + 2];

                dx = x1 - x2;
                dy = y1 - y2;
                dz = z1 - z2;

                // We don't need the scale since we normalize
                expr = expf(factor * (dx*dx + dy*dy + dz*dz));
                value = postprob * expr;

                obj->sum_P_p_x_O[iParticle] += value;
                total_sum_P_p_x_O += value;

            }

        }

        // Compute p(x_j,i|O) and update weights

        uniform = (1.0f/((float) obj->nParticles));
        alpha = postprobs->arrayTrackTotal[iTrack];
        oneminusalpha = (1.0f - alpha);
        alphanorm = alpha / total_sum_P_p_x_O;

        total_w = obj->epsilon;

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            p_x_O = oneminusalpha * uniform + alphanorm * obj->sum_P_p_x_O[iParticle];
            particles->array[iParticle * 7 + 6] *= p_x_O;
            total_w += particles->array[iParticle * 7 + 6];

        }

        Neff = obj->epsilon;

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            particles->array[iParticle * 7 + 6] /= total_w;
            Neff += particles->array[iParticle * 7 + 6] * particles->array[iParticle * 7 + 6];
            
        }

        // Resample if needed

        Neff = 1.0f / Neff;

        if (Neff < (obj->Nmin * (float) obj->nParticles)) {
            
            memcpy(obj->particles->array, particles->array, sizeof(float) * 7 * obj->nParticles);

            for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {
                
                obj->pdf_weight[iParticle] = obj->particles->array[iParticle * 7 + 6];

            }

            random_pdf(obj->rnd_weight, obj->pdf_weight);
            random_generate(obj->rnd_weight, obj->nParticles, obj->indexes_weight);
            random_generate(obj->rnd_ratio, obj->nParticles, obj->indexes_ratio);
            uniform = (1.0f/((float) obj->nParticles));

            for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

                particles->array[iParticle * 7 + 0] = obj->particles->array[obj->indexes_weight[iParticle] * 7 + 0];
                particles->array[iParticle * 7 + 1] = obj->particles->array[obj->indexes_weight[iParticle] * 7 + 1];
                particles->array[iParticle * 7 + 2] = obj->particles->array[obj->indexes_weight[iParticle] * 7 + 2];
                particles->array[iParticle * 7 + 3] = obj->particles->array[obj->indexes_weight[iParticle] * 7 + 3];
                particles->array[iParticle * 7 + 4] = obj->particles->array[obj->indexes_weight[iParticle] * 7 + 4];
                particles->array[iParticle * 7 + 5] = obj->particles->array[obj->indexes_weight[iParticle] * 7 + 5];

                particles->state[iParticle] = (unsigned char) obj->indexes_ratio[iParticle];

                particles->array[iParticle * 7 + 6] = uniform;

            }

        }

    }

    void particle2particle_update_static(particle2particle_obj * obj, const postprobs_obj * postprobs, const unsigned int iTrack, const pots_obj * pots, particles_obj * particles) {

        // Do nothing: keep old particles distribution

    }

    void particle2particle_estimate(const particle2particle_obj * obj, const particles_obj * particles, float * x, float * y, float * z) {

        unsigned int iParticle;
        float xTotal, yTotal, zTotal;
        
        xTotal = 0.0f;
        yTotal = 0.0f;
        zTotal = 0.0f;

        for (iParticle = 0; iParticle < particles->nParticles; iParticle++) {

            xTotal += particles->array[iParticle * 7 + 6] * particles->array[iParticle * 7 + 0];
            yTotal += particles->array[iParticle * 7 + 6] * particles->array[iParticle * 7 + 1];
            zTotal += particles->array[iParticle * 7 + 6] * particles->array[iParticle * 7 + 2];

        }

        *x = xTotal;
        *y = yTotal;
        *z = zTotal;

    }
