#ifndef __ODAS_INIT_SCANNING
#define __ODAS_INIT_SCANNING

    #include "../general/mic.h"
    #include "../general/soundspeed.h"
    #include "../general/spatialfilter.h"

    #include "../signal/beampattern.h"
    #include "../signal/scan.h"
    #include "../signal/spatialgain.h"
    #include "../signal/spatialindex.h"
    #include "../signal/spatialmask.h"
    #include "../signal/map.h"
    #include "../signal/pair.h"
    #include "../signal/tau.h"

    #include "../init/delay.h"
    #include "../init/directivity.h"
    #include "../init/hit.h"
    #include "../init/linking.h"
    #include "../init/space.h"

    scans_obj * scanning_init_scans(const mics_obj * mics, const spatialfilter_obj * spatialfilter, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const unsigned int nMatches, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels, const unsigned int nThetas, const float gainMin, const unsigned int interpRate);

#endif