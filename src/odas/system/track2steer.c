
   /**
    * \file     track2steer.c
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
    
    #include <system/track2steer.h>

    track2steer_obj * track2steer_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float c, const unsigned int fS, const float * mics) {

        track2steer_obj * obj;
        unsigned int iBin;

        obj = (track2steer_obj *) malloc(sizeof(track2steer_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->c = c;
        obj->fS = fS;

        obj->mics = (float *) malloc(sizeof(float) * nChannels * 3);
        memcpy(obj->mics, mics, sizeof(float) * nChannels * 3);        

        obj->factor = (float *) malloc(sizeof(float) * halfFrameSize);

        for (iBin = 0; iBin < halfFrameSize; iBin++) {

            obj->factor[iBin] = -2.0f * M_PI * ((float) iBin) / ((float) ((halfFrameSize-1) * 2));

        }

        obj->speed = ((float) obj->fS) / obj->c;

        return obj;

    }

    void track2steer_destroy(track2steer_obj * obj) {

        unsigned int iBin;

        free((void *) obj->factor);
        free((void *) obj->mics);

        free((void *) obj);

    }

    void track2steer_process(track2steer_obj * obj, const tracks_obj * tracks, const gains_obj * gains, const masks_obj * masks, steers_obj * steers) {

        unsigned int iSep;
        unsigned int iBin;
        unsigned int iChannel;
        
        float dist;
        float delay;
        float gain;
        char mask;
        
        float Areal;
        float Aimag;

        unsigned int iSampleSC;
        unsigned int iSampleBC;        

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleSC = iSep * obj->nChannels + iChannel;
                    mask = masks->array[iSampleSC];

                    if (mask == 1) {                   

                        dist = tracks->array[iSep * 3 + 0] * obj->mics[iChannel * 3 + 0] + 
                               tracks->array[iSep * 3 + 1] * obj->mics[iChannel * 3 + 1] +
                               tracks->array[iSep * 3 + 2] * obj->mics[iChannel * 3 + 2]; 

                        delay = -1.0f * obj->speed * dist;

                        gain = gains->array[iSampleSC];

                        for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                            iSampleBC = iBin * obj->nChannels + iChannel;

                            Areal = gain * cosf(obj->factor[iBin] * delay);
                            Aimag = gain * sinf(obj->factor[iBin] * delay);

                            steers->array[iSep][iSampleBC * 2 + 0] = Areal;
                            steers->array[iSep][iSampleBC * 2 + 1] = Aimag;

                        }

                    }

                }

            }
            else {

                memset(steers->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize * obj->nChannels * 2);

            }

        }

    }
