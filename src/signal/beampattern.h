#ifndef __ODAS_SIGNAL_BEAMPATTERN
#define __ODAS_SIGNAL_BEAMPATTERN

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct beampatterns_obj {

        unsigned int nChannels;
        unsigned int nThetas;

        float * minThetas;
        float * maxThetas;
        float * deltaThetas;
                        
        float * gains;

    } beampatterns_obj;

    beampatterns_obj * beampatterns_construct_zero(const unsigned int nChannels, const unsigned int nThetas);

    void beampatterns_destroy(beampatterns_obj * obj);

    void beampatterns_printf(const beampatterns_obj * obj);

#endif