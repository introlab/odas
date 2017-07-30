#ifndef __ODAS_SIGNAL_SPATIALFILTER
#define __ODAS_SIGNAL_SPATIALFILTER

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct spatialfilter_obj {

        float * direction;
        float thetaAllPass;
        float thetaNoPass;

    } spatialfilter_obj;

    spatialfilter_obj * spatialfilter_construct_zero(void);

    spatialfilter_obj * spatialfilter_clone(const spatialfilter_obj * obj);

    void spatialfilter_destroy(spatialfilter_obj * obj); 

    void spatialfilter_printf(const spatialfilter_obj * obj);   

#endif