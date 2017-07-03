
    #include "directivity.h"

    beampatterns_obj * directivity_beampattern(const mics_obj * mics, const unsigned int nThetas) {

        beampatterns_obj * obj;
        
        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int iTheta;
        float theta;
        float xap, xnp, x0;
        float alpha;

        nChannels = mics->nChannels;

        obj = beampatterns_construct_zero(nChannels, nThetas);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            obj->minThetas[iChannel] = 0.0f;
            obj->maxThetas[iChannel] = 180.0f;
            obj->deltaThetas[iChannel] = (obj->maxThetas[iChannel] - obj->minThetas[iChannel]) / ((float) (nThetas - 1));

            for (iTheta = 0; iTheta < nThetas; iTheta++) {

                theta = ((float) iTheta) * obj->deltaThetas[iChannel] + obj->minThetas[iChannel];

                if (theta <= mics->thetaAllPass[iChannel]) {

                    obj->gains[iChannel * nThetas  + iTheta] = 1.0f;

                }
                else if (theta >= mics->thetaNoPass[iChannel]) {

                    obj->gains[iChannel * nThetas  + iTheta] = 0.0f;

                }
                else {

                    xap = mics->thetaAllPass[iChannel];
                    xnp = mics->thetaNoPass[iChannel];

                    x0 = (xap + xnp) / 2.0f;
                    alpha = 20.0f / (xnp - xap);

                    obj->gains[iChannel * nThetas  + iTheta] = 1.0f / (1.0f + expf(alpha * (theta - x0)));

                }

            }

        }

        return obj;

    }

    spatialgains_obj * directivity_spatialgains(const mics_obj * mics, const beampatterns_obj * beampatterns, const points_obj * points) {

        spatialgains_obj * obj;

        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int nPoints;
        unsigned int iPoint;
        float dx, dy, dz, dNorm;
        float ux, uy, uz, uNorm;
        float proj;
        float theta;
        signed int iTheta;
        unsigned int nThetas;
        float gain;

        nChannels = mics->nChannels;
        nPoints = points->nPoints;
        nThetas = beampatterns->nThetas;

        obj = spatialgains_construct_zero(nChannels, nPoints);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            dx = mics->direction[iChannel * 3 + 0];
            dy = mics->direction[iChannel * 3 + 1];
            dz = mics->direction[iChannel * 3 + 2];

            dNorm = sqrtf(dx * dx + dy * dy + dz * dz);

            for (iPoint = 0; iPoint < nPoints; iPoint++) {

                ux = points->array[iPoint * 3 + 0];
                uy = points->array[iPoint * 3 + 1];
                uz = points->array[iPoint * 3 + 2];

                uNorm = sqrtf(ux * ux + uy * uy + uz * uz);

                proj = dx * ux + dy * uy + dz * uz;

                theta = (360.0f/(2.0f * M_PI)) * acosf(proj / (dNorm * uNorm));

                iTheta = roundf((theta - beampatterns->minThetas[iChannel]) / (beampatterns->deltaThetas[iChannel]) + beampatterns->minThetas[iChannel]);

                if (iTheta < 0) {
                    iTheta = 0;
                }
                if (iTheta >= nThetas) {
                    iTheta = nThetas - 1;
                }

                gain = beampatterns->gains[iChannel * nThetas + iTheta];

                obj->array[iPoint * nChannels + iChannel] = gain;

            }

        }

        return obj;

    }

    spatialmasks_obj * directivity_spatialmasks(const spatialgains_obj * spatialgains, const float gainMin) {

        spatialmasks_obj * obj;

        unsigned int nChannels;
        unsigned int nPairs;
        unsigned int nPoints;

        unsigned int iChannel1, iChannel2;
        unsigned int iPair;
        unsigned int iPoint;
        float gain;

        nChannels = spatialgains->nChannels;
        nPairs = nChannels * (nChannels - 1) / 2;
        nPoints = spatialgains->nPoints;

        obj = spatialmasks_construct_zero(nPoints, nPairs);

        for (iPoint = 0; iPoint < nPoints; iPoint++) {

            iPair = 0;

            for (iChannel1 = 0; iChannel1 < nChannels; iChannel1++) {

                for (iChannel2 = (iChannel1 + 1); iChannel2 < nChannels; iChannel2++) {

                    gain = spatialgains->array[iPoint * nChannels + iChannel1] * spatialgains->array[iPoint * nChannels + iChannel2];

                    if (gain >= gainMin) {
                        
                        obj->array[iPoint * nPairs + iPair] = 0x01;

                    }
                    else {

                        obj->array[iPoint * nPairs + iPair] = 0x00;

                    }

                    iPair++;

                }

            }

        }

        return obj;

    }

    spatialindexes_obj * directivity_spatialindexes(const spatialmasks_obj * spatialmasks) {

        spatialindexes_obj * obj;

        unsigned int nPoints;
        unsigned int nPairs;
        unsigned int iPoint;
        unsigned int iPair;

        nPoints = spatialmasks->nPoints;
        nPairs = spatialmasks->nPairs;

        obj = spatialindexes_construct_zero(nPoints, nPairs);

        for (iPoint = 0; iPoint < nPoints; iPoint++) {

            obj->count[iPoint] = 0;

            for (iPair = 0; iPair < nPairs; iPair++) {

                if (spatialmasks->array[iPoint * nPairs + iPair] == 0x01) {

                    obj->array[iPoint * nPairs + obj->count[iPoint]] = iPair; 
                    obj->count[iPoint]++;              

                }

            }

        }

        return obj;

    }

    pairs_obj * directivity_pairs(const spatialmasks_obj * spatialmasks) {

        pairs_obj * obj;

        unsigned int nPoints;
        unsigned int nPairs;
        unsigned int iPoint;
        unsigned int iPair;

        nPoints = spatialmasks->nPoints;
        nPairs = spatialmasks->nPairs;

        obj = pairs_construct_zero(nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {

            for (iPoint = 0; iPoint < nPoints; iPoint++) {

                if (spatialmasks->array[iPoint * nPairs + iPair] == 0x01) {

                    obj->array[iPair] = 0x01;
                    break;

                }

            }

        }

        return obj;

    }

    void directivity_pairsadd(pairs_obj * destPairs, const pairs_obj * srcPairs) {

        unsigned int iPair;
        unsigned int nPairs;

        nPairs = srcPairs->nPairs;

        for (iPair = 0; iPair < nPairs; iPair++) {

            if (srcPairs->array[iPair] == 0x01) {

                destPairs->array[iPair] = 0x01;

            }

        }

    }