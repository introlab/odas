#ifndef __ODAS_SIGNAL_PARTICLE
#define __ODAS_SIGNAL_PARTICLE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct particles_obj {

        unsigned int nParticles;
        float * array;
        unsigned char * state;

    } particles_obj;

    particles_obj * particles_construct_zero(const unsigned int nParticles);

    void particles_destroy(particles_obj * obj);

    void particles_printf(const particles_obj * obj);

#endif