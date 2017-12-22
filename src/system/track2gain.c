    
    #include "track2gain.h"

    track2gain_obj * track2gain_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float * directions, const float * direction) {

        track2gain_obj * obj;

        obj = (track2gain_obj *) malloc(sizeof(track2gain_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;

        obj->directions = (float *) malloc(sizeof(float) * nChannels * 3);
        memcpy(obj->directions, directions, sizeof(float) * nChannels * 3);

        obj->direction = (float *) malloc(sizeof(float) * 3);
        memcpy(obj->direction, direction, sizeof(float) * 3);

        return obj;

    }

    void track2gain_destroy(track2gain_obj * obj) {
        
        free((void *) obj->directions);
        free((void *) obj->direction);
        free((void *) obj);

    }

    void track2gain_process(track2gain_obj * obj, const beampatterns_obj * beampatterns_mics, const beampatterns_obj * beampatterns_spatialfilter, const tracks_obj * tracks, gains_obj * gains) {

        unsigned int iSep;
        unsigned int iChannel;
        
        unsigned int iThetaMic;
        unsigned int iThetaFilter;
        
        float ux, uy, uz;
        float uNorm;
        float dx, dy, dz;
        float dNorm;
        float sx, sy, sz;
        float sNorm;

        float projMic;
        float projFilter;
        float thetaMic;
        float thetaFilter;
        float gainMic;
        float gainFilter;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                ux = tracks->array[iSep * 3 + 0];
                uy = tracks->array[iSep * 3 + 1];
                uz = tracks->array[iSep * 3 + 2];

                uNorm = sqrtf(ux * ux + uy * uy + uz * uz);

                sx = obj->direction[0];
                sy = obj->direction[1];
                sz = obj->direction[2];

                sNorm = sqrtf(sx * sx + sy * sy + sz * sz);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    dx = obj->directions[iChannel * 3 + 0];
                    dy = obj->directions[iChannel * 3 + 1];
                    dz = obj->directions[iChannel * 3 + 2];

                    dNorm = sqrtf(dx * dx + dy * dy + dz * dz);

                    projMic = dx * ux + dy * uy + dz * uz;
                    projFilter = sx * ux + sy * uy + sz * uz;

                    thetaMic = (360.0f/(2.0f * M_PI)) * acosf(projMic / (dNorm * uNorm));
                    thetaFilter = (360.0f/(2.0f * M_PI)) * acosf(projFilter / (sNorm * uNorm));

                    iThetaMic = roundf((thetaMic - beampatterns_mics->minThetas[iChannel]) / (beampatterns_mics->deltaThetas[iChannel]) + beampatterns_mics->minThetas[iChannel]);
                    iThetaFilter = roundf((thetaFilter - beampatterns_spatialfilter->minThetas[0]) / (beampatterns_spatialfilter->deltaThetas[0]) + beampatterns_spatialfilter->minThetas[0]);

                    if (iThetaMic < 0) {
                        iThetaMic = 0;
                    }
                    if (iThetaMic >= beampatterns_mics->nThetas) {
                        iThetaMic = beampatterns_mics->nThetas - 1;
                    }

                    if (iThetaFilter < 0) {
                        iThetaFilter = 0;
                    }
                    if (iThetaFilter >= beampatterns_spatialfilter->nThetas) {
                        iThetaFilter = beampatterns_spatialfilter->nThetas - 1;
                    }                    

                    gainMic = beampatterns_mics->gains[iChannel * beampatterns_mics->nThetas + iThetaMic];
                    gainFilter = beampatterns_spatialfilter->gains[iThetaFilter];

                    gains->array[iSep * obj->nChannels + iChannel] = gainMic * gainFilter;

                }  

            }
            else {

                memset(&(gains->array[iSep * obj->nChannels]), 0x00, sizeof(float) * obj->nChannels);

            }

        }

    }