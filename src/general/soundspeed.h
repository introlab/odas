#ifndef __ODAS_GENERAL_SOUNDSPEED
#define __ODAS_GENERAL_SOUNDSPEED

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct soundspeed_obj {

        float mu;
        float sigma2;

    } soundspeed_obj;

    soundspeed_obj * soundspeed_construct_zero(void);

    soundspeed_obj * soundspeed_clone(const soundspeed_obj * obj);

    void soundspeed_destroy(soundspeed_obj * obj);

    void soundspeed_printf(const soundspeed_obj * obj);

#endif