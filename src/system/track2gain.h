#ifndef __ODAS_SYSTEM_TRACK2GAIN
#define __ODAS_SYSTEM_TRACK2GAIN

    #include "../signal/beampattern.h"
    #include "../signal/track.h"
    #include "../signal/gain.h"

    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    typedef struct track2gain_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float * directions;

    } track2gain_obj;

    track2gain_obj * track2gain_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float * directions);

    void track2gain_destroy(track2gain_obj * obj);

    void track2gain_process(track2gain_obj * obj, const beampatterns_obj * beampatterns, const tracks_obj * tracks, gains_obj * gains);


#endif