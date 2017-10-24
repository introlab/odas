#ifndef __ODAS_SYSTEM_ENV2ENV
#define __ODAS_SYSTEM_ENV2ENV

    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    #include "../signal/env.h"

    typedef struct env2env_mcra_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        unsigned int bSize;
        float alphaS;
        unsigned int L;
        float delta;
        float alphaD;

        unsigned int l;

        float * b;
        float ** S;
        float ** Smin;
        float ** SminPrev;
        float ** SPrev;
        float ** Stmp;
        float ** StmpPrev;
        float ** Sf;
        float ** lambdaD;
        float ** lambdaDnext;

    } env2env_mcra_obj;

    env2env_mcra_obj * env2env_mcra_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const unsigned int bSize, const float alphaS, const unsigned int L, const float delta, const float alphaD);

    void env2env_mcra_destroy(env2env_mcra_obj * obj);

    void env2env_mcra_process(env2env_mcra_obj * obj, const envs_obj * noisy, envs_obj * noise);


#endif