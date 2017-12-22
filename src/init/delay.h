#ifndef __ODAS_INIT_DELAY
#define __ODAS_INIT_DELAY

    #include <math.h>

    #include "../general/mic.h"
    #include "../general/soundspeed.h"

    #include "../signal/delta.h"
    #include "../signal/point.h"
    #include "../signal/tdoa.h"
    #include "../signal/tau.h"

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize, const unsigned int interpRate);

    //tdoas_obj * delay_tdoas_minmax(const tdoas_obj * tdoas, const deltas_obj * deltas);

    //void delay_tdoas_allminmax(tdoas_obj * tdoas, const tdoas_obj * minmax);

    taus_obj * delay_taus(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize, const unsigned int interpRate);

#endif

    