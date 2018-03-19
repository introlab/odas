
   /**
    * \file     directivity.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <init/directivity.h>

    beampatterns_obj * directivity_beampattern_mics(const mics_obj * mics, const unsigned int nThetas) {

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

    beampatterns_obj * directivity_beampattern_spatialfilter(const spatialfilter_obj * spatialfilter, const unsigned int nThetas) {

        beampatterns_obj * obj;
        
        unsigned int iTheta;
        float theta;
        float xap, xnp, x0;
        float alpha;

        obj = beampatterns_construct_zero(1, nThetas);

        obj->minThetas[0] = 0.0f;
        obj->maxThetas[0] = 180.0f;
        obj->deltaThetas[0] = (obj->maxThetas[0] - obj->minThetas[0]) / ((float) (nThetas - 1));

        for (iTheta = 0; iTheta < nThetas; iTheta++) {

            theta = ((float) iTheta) * obj->deltaThetas[0] + obj->minThetas[0];

            if (theta <= spatialfilter->thetaAllPass) {

                obj->gains[iTheta] = 1.0f;

            }
            else if (theta >= spatialfilter->thetaNoPass) {

                obj->gains[iTheta] = 0.0f;

            }
            else {

                xap = spatialfilter->thetaAllPass;
                xnp = spatialfilter->thetaNoPass;

                x0 = (xap + xnp) / 2.0f;
                alpha = 20.0f / (xnp - xap);

                obj->gains[iTheta] = 1.0f / (1.0f + expf(alpha * (theta - x0)));

            }

        }

        return obj;

    }

    spatialgains_obj * directivity_spatialgains(const mics_obj * mics, const beampatterns_obj * beampatterns_mics, const spatialfilter_obj * spatialfilter, const beampatterns_obj * beampatterns_spatialfilter, const points_obj * points) {

        spatialgains_obj * obj;

        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int nPoints;
        unsigned int iPoint;
        float dx, dy, dz, dNorm;
        float sx, sy, sz, sNorm;
        float ux, uy, uz, uNorm;
        float projMic;
        float projFilter;
        float thetaMic;
        float thetaFilter;
        signed int iThetaMic;
        signed int iThetaFilter;
        unsigned int nThetasMic;
        unsigned int nThetasFilter;

        float gainMic;
        float gainFilter;

        nChannels = mics->nChannels;
        nPoints = points->nPoints;
        nThetasMic = beampatterns_mics->nThetas;
        nThetasFilter = beampatterns_spatialfilter->nThetas;

        obj = spatialgains_construct_zero(nChannels, nPoints);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            dx = mics->direction[iChannel * 3 + 0];
            dy = mics->direction[iChannel * 3 + 1];
            dz = mics->direction[iChannel * 3 + 2];

            dNorm = sqrtf(dx * dx + dy * dy + dz * dz);

            sx = spatialfilter->direction[0];
            sy = spatialfilter->direction[1];
            sz = spatialfilter->direction[2];

            sNorm = sqrtf(sx * sx + sy * sy + sz * sz);

            for (iPoint = 0; iPoint < nPoints; iPoint++) {

                ux = points->array[iPoint * 3 + 0];
                uy = points->array[iPoint * 3 + 1];
                uz = points->array[iPoint * 3 + 2];

                uNorm = sqrtf(ux * ux + uy * uy + uz * uz);

                projMic = dx * ux + dy * uy + dz * uz;
                projFilter = sx * ux + sy * uy + sz * uz;

                thetaMic = (360.0f/(2.0f * M_PI)) * acosf(projMic / (dNorm * uNorm));
                thetaFilter = (360.0f/(2.0f * M_PI)) * acosf(projFilter / (sNorm * uNorm));

                iThetaMic = roundf((thetaMic - beampatterns_mics->minThetas[iChannel]) / (beampatterns_mics->deltaThetas[iChannel]) + beampatterns_mics->minThetas[iChannel]);
                iThetaFilter = roundf((thetaFilter - beampatterns_spatialfilter->minThetas[0]) / (beampatterns_spatialfilter->deltaThetas[0]) + beampatterns_spatialfilter->minThetas[0]);

                if (iThetaMic < 0) {
                    iThetaMic = 0;
                }
                if (iThetaMic >= nThetasMic) {
                    iThetaMic = nThetasMic - 1;
                }

                if (iThetaFilter < 0) {
                    iThetaFilter = 0;
                }
                if (iThetaFilter >= nThetasFilter) {
                    iThetaFilter = nThetasFilter - 1;
                }                

                gainMic = beampatterns_mics->gains[iChannel * nThetasMic + iThetaMic];
                gainFilter = beampatterns_spatialfilter->gains[iThetaFilter];

                obj->array[iPoint * nChannels + iChannel] = gainMic * gainFilter;

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
