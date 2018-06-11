
   /**
    * \file     demixing2freq.c
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
    
    #include <system/demixing2freq.h>

    demixing2freq_obj * demixing2freq_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize) {

        demixing2freq_obj * obj;

        obj = (demixing2freq_obj *) malloc(sizeof(demixing2freq_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void demixing2freq_destroy(demixing2freq_obj * obj) {

        free((void *) obj);

    }

    void demixing2freq_process(demixing2freq_obj * obj, const tracks_obj * tracks, const demixings_obj * demixings, const masks_obj * masks, const freqs_obj * freqsChannel, freqs_obj * freqsSeparated) {

        unsigned int iSep;
        unsigned int iChannel;
        unsigned int iBin;
        
        unsigned int iSampleSC;
        unsigned int iSampleBC;
        unsigned int iSampleB;

        float Xreal;
        float Ximag;
        float Wreal;
        float Wimag;
        float Yreal;
        float Yimag;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                memset(freqsSeparated->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize * 2);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleSC = iSep * obj->nChannels + iChannel;

                    if (masks->array[iSampleSC] == 1) {                       

                        for (iBin = 0; iBin < obj->halfFrameSize; iBin++)                 {

                            iSampleBC = iBin * obj->nChannels + iChannel;
                            iSampleB = iBin;

                            Xreal = freqsChannel->array[iChannel][iSampleB * 2 + 0];
                            Ximag = freqsChannel->array[iChannel][iSampleB * 2 + 1];

                            Wreal = demixings->array[iSep][iSampleBC * 2 + 0];
                            Wimag = demixings->array[iSep][iSampleBC * 2 + 1];

                            Yreal = Wreal * Xreal - Wimag * Ximag;
                            Yimag = Wreal * Ximag + Wimag * Xreal;

                            freqsSeparated->array[iSep][iSampleB * 2 + 0] += Yreal;
                            freqsSeparated->array[iSep][iSampleB * 2 + 1] += Yimag;

                        }

                    }

                }

            }
            else {

                memset(freqsSeparated->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize * 2);

            }

        }

    }
