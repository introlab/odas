    
    #include "steer2freq.h"

    steer2freq_obj * steer2freq_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize) {

        steer2freq_obj * obj;

        obj = (steer2freq_obj *) malloc(sizeof(steer2freq_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void steer2freq_destroy(steer2freq_obj * obj) {

        free((void *) obj);

    }

    void steer2freq_process(steer2freq_obj * obj, const tracks_obj * tracks, const steers_obj * demixing, const masks_obj * masks, const freqs_obj * freqsChannel, freqs_obj * freqsSeparated) {

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

                            Wreal = demixing->array[iSep][iSampleBC * 2 + 0];
                            Wimag = demixing->array[iSep][iSampleBC * 2 + 1];

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