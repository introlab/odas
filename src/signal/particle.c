    
    #include "particle.h"
    
    particles_obj * particles_construct_zero(const unsigned int nParticles) {

        particles_obj * obj;

        obj = (particles_obj *) malloc(sizeof(particles_obj));

        obj->nParticles = nParticles;

        obj->array = (float *) malloc(sizeof(float) * 7 * nParticles);
        memset(obj->array, 0x00, sizeof(float) * 7 * nParticles);

        obj->state = (unsigned char *) malloc(sizeof(unsigned char) * nParticles);
        memset(obj->state, 0x00, sizeof(unsigned char) * nParticles);

        return obj;

    }

    void particles_destroy(particles_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->state);
        free((void *) obj);

    }

    void particles_printf(const particles_obj * obj) {

        unsigned int iParticle;

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            printf("(%04u): x = (%+1.3f,%+1.3f,%+1.3f), v = (%+1.3f,%+1.3f,%+1.3f), w = %1.5f, s = %u\n",
                   iParticle,
                   obj->array[iParticle * 7 + 0],
                   obj->array[iParticle * 7 + 1],
                   obj->array[iParticle * 7 + 2],
                   obj->array[iParticle * 7 + 3],
                   obj->array[iParticle * 7 + 4],
                   obj->array[iParticle * 7 + 5],
                   obj->array[iParticle * 7 + 6],
                   obj->state[iParticle]);

        }

    }