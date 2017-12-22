#ifndef __ODAS_SYSTEM_MIXTURE2MIXTURE
#define __ODAS_SYSTEM_MIXTURE2MIXTURE

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    #include "../utils/gaussian.h"
    #include "../signal/coherence.h"
    #include "../signal/mixture.h"
    #include "../signal/pot.h"
    #include "../signal/postprob.h"

    typedef struct mixture2mixture_obj {

        gaussians_1d_obj * active;
        gaussians_1d_obj * inactive;
        float diffuse;

        float Pfalse;
        float Pnew;
        float Ptrack;
        float epsilon;

    } mixture2mixture_obj;

    mixture2mixture_obj * mixture2mixture_construct(const gaussians_1d_obj * active_gmm, const gaussians_1d_obj * inactive_gmm, const float diffuse_cst, const float Pfalse, const float Pnew, const float Ptrack, const float epsilon);

    void mixture2mixture_destroy(mixture2mixture_obj * obj);

    void mixture2mixture_process(mixture2mixture_obj * obj, mixture_obj * mixture, const pots_obj * pots, const coherences_obj * coherences, postprobs_obj * postprobs);

#endif