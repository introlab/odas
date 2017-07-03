#ifndef __ODAS_SIGNAL_MIXTURE
#define __ODAS_SIGNAL_MIXTURE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../signal/assignation.h"
    #include "../init/combining.h"

    typedef struct mixture_obj {
       
        unsigned int nPots;
        unsigned int nTracks;
        unsigned int nTracksNewFalse;
        unsigned int nCombinations;

        assignations_obj * assignations;

        float * p_Ez_AICD;
        float * p_Eszs_phics;
        float * p_phics;
        float * p_Ez_phic;
        float * p_phic;
        float * p_phic_Ez;

    } mixture_obj;

    mixture_obj * mixture_construct_zero(const unsigned int nPots, const unsigned int nTracks);

    void mixture_destroy(mixture_obj * obj);

    void mixture_printf(const mixture_obj * obj);

#endif