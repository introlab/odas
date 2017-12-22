#ifndef __ODAS_SYSTEM_FREQ2ENV
#define __ODAS_SYSTEM_FREQ2ENV

    #include <stdlib.h>

    #include "../signal/freq.h"
    #include "../signal/env.h"

    typedef struct freq2env_obj {

        unsigned int halfFrameSize;

    } freq2env_obj;

    freq2env_obj * freq2env_construct_zero(const unsigned int halfFrameSize);

    void freq2env_destroy(freq2env_obj * obj);

    void freq2env_process(freq2env_obj * obj, const freqs_obj * freqs, envs_obj * envs);

#endif