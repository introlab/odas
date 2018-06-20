#ifndef __ODAS_DEMO_CORE_PARAMETERS
#define __ODAS_DEMO_CORE_PARAMETERS

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>

    typedef struct profiler {


    } profiler;

    profiler * profiler_construct(void);

    void profiler_destroy(profiler * prf);

    void profiler_printf(const profiler * prf);

#endif