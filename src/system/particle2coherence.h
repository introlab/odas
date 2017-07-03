#ifndef __ODAS_SYSTEM_PARTICLE2COHERENCE
#define __ODAS_SYSTEM_PARTICLE2COHERENCE

    #include "../utils/gaussian.h"
    #include "../signal/particle.h"
    #include "../signal/coherence.h"
    #include "../signal/pot.h"

    typedef struct particle2coherence_obj {

        float sigmaR;
        float expScale;
        float expFactor;

    } particle2coherence_obj;

    particle2coherence_obj * particle2coherence_construct(const float sigmaR);

    void particle2coherence_destroy(particle2coherence_obj * obj);

    void particle2coherence_process(particle2coherence_obj * obj, const particles_obj * particles, const pots_obj * pots, const unsigned int iTrack, coherences_obj * coherences);

#endif