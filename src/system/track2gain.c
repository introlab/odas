
   /**
    * \file     track2gain.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */
    
    #include <system/track2gain.h>

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

    void track2gain_process(track2gain_obj * obj, const beampatterns_obj * beampatterns_mics, const tracks_obj * tracks, gains_obj * gains) {

        unsigned int iSep;
        unsigned int iChannel;
        
        unsigned int iThetaMic;
        unsigned int iThetaFilter;
        
        float ux, uy, uz;
        float uNorm;
        float dx, dy, dz;
        float dNorm;

        float projMic;
        float thetaMic;
        float gainMic;

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

                    projMic = dx * ux + dy * uy + dz * uz;
                    thetaMic = (360.0f/(2.0f * M_PI)) * acosf(projMic / (dNorm * uNorm));
                    iThetaMic = roundf((thetaMic - beampatterns_mics->minThetas[iChannel]) / (beampatterns_mics->deltaThetas[iChannel]) + beampatterns_mics->minThetas[iChannel]);

                    if (iThetaMic < 0) {
                        iThetaMic = 0;
                    }
                    if (iThetaMic >= beampatterns_mics->nThetas) {
                        iThetaMic = beampatterns_mics->nThetas - 1;
                    }

                    gainMic = beampatterns_mics->gains[iChannel * beampatterns_mics->nThetas + iThetaMic];

                    gains->array[iSep * obj->nChannels + iChannel] = gainMic;

                }  

            }
            else {

                memset(&(gains->array[iSep * obj->nChannels]), 0x00, sizeof(float) * obj->nChannels);

            }

        }

    }
