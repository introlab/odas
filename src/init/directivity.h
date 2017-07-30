#ifndef __ODAS_INIT_DIRECTIVITY
#define __ODAS_INIT_DIRECTIVITY

    #include <stdlib.h>
    #include <math.h>

    #include "../general/mic.h"
    #include "../general/spatialfilter.h"

    #include "../signal/beampattern.h"
    #include "../signal/pair.h"
    #include "../signal/point.h"
    #include "../signal/spatialgain.h"
    #include "../signal/spatialindex.h"
    #include "../signal/spatialmask.h"

    beampatterns_obj * directivity_beampattern_mics(const mics_obj * mics, const unsigned int nThetas);

    beampatterns_obj * directivity_beampattern_spatialfilter(const spatialfilter_obj * spatialfilter, const unsigned int nThetas);

    spatialgains_obj * directivity_spatialgains(const mics_obj * mics, const beampatterns_obj * beampatterns_mics, const spatialfilter_obj * spatialfilter, const beampatterns_obj * beampatterns_spatialfilter, const points_obj * points);

    spatialmasks_obj * directivity_spatialmasks(const spatialgains_obj * spatialgains, const float minGain);

    spatialindexes_obj * directivity_spatialindexes(const spatialmasks_obj * spatialmasks);

    pairs_obj * directivity_pairs(const spatialmasks_obj * spatialmasks);

    void directivity_pairsadd(pairs_obj * destPairs, const pairs_obj * srcPairs);

#endif