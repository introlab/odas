    
    #include "track2gain.h"

    track2gain_obj * track2gain_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float * directions) {

        track2gain_obj * obj;

        obj = (track2gain_obj *) malloc(sizeof(track2gain_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;

        obj->directions = (float *) malloc(sizeof(float) * nChannels * 3);
        memcpy(obj->directions, directions, sizeof(float) * nChannels * 3);

        return obj;

    }

    void track2gain_destroy(track2gain_obj * obj) {
        
        free((void *) obj->directions);
        free((void *) obj);

    }

    void track2gain_process(track2gain_obj * obj, const beampatterns_obj * beampatterns, const tracks_obj * tracks, gains_obj * gains) {

        unsigned int iSep;
        unsigned int iChannel;
        unsigned int iTheta;
        
        float ux, uy, uz;
        float uNorm;
        float dx, dy, dz;
        float dNorm;

        float proj;
        float theta;
        float gain;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                ux = tracks->array[iSep * 3 + 0];
                uy = tracks->array[iSep * 3 + 1];
                uz = tracks->array[iSep * 3 + 2];

                uNorm = sqrtf(ux * ux + uy * uy + uz * uz);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    dx = obj->directions[iChannel * 3 + 0];
                    dy = obj->directions[iChannel * 3 + 1];
                    dz = obj->directions[iChannel * 3 + 2];

                    dNorm = sqrtf(dx * dx + dy * dy + dz * dz);

                    proj = dx * ux + dy * uy + dz * uz;

                    theta = (360.0f/(2.0f * M_PI)) * acosf(proj / (dNorm * uNorm));

                    iTheta = roundf((theta - beampatterns->minThetas[iChannel]) / (beampatterns->deltaThetas[iChannel]) + beampatterns->minThetas[iChannel]);

                    if (iTheta < 0) {
                        iTheta = 0;
                    }
                    if (iTheta >= beampatterns->nThetas) {
                        iTheta = beampatterns->nThetas - 1;
                    }

                    gain = beampatterns->gains[iChannel * beampatterns->nThetas + iTheta];

                    gains->array[iSep * obj->nChannels + iChannel] = gain;

                }        

            }
            else {

                memset(&(gains->array[iSep * obj->nChannels]), 0x00, sizeof(float) * obj->nChannels);

            }

        }

    }