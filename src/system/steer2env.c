    
    #include "steer2env.h"

    steer2env_obj * steer2env_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize) {

        steer2env_obj * obj;

        obj = (steer2env_obj *) malloc(sizeof(steer2env_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void steer2env_destroy(steer2env_obj * obj) {

        free((void *) obj);

    }

    void steer2env_process(steer2env_obj * obj, const tracks_obj * tracks, const steers_obj * demixing, const masks_obj * masks, const freqs_obj * freqs, envs_obj * envs) {

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

                memset(envs->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleSC = iSep * obj->nChannels + iChannel;

                    if (masks->array[iSampleSC] == 1) {

                        for (iBin = 0; iBin < obj->halfFrameSize; iBin++)                 {

                            iSampleBC = iBin * obj->nChannels + iChannel;
                            iSampleB = iBin;

                            Xreal = freqs->array[iChannel][iSampleB * 2 + 0];
                            Ximag = freqs->array[iChannel][iSampleB * 2 + 1];

                            Wreal = demixing->array[iSep][iSampleBC * 2 + 0];
                            Wimag = demixing->array[iSep][iSampleBC * 2 + 1];

                            Yreal = Wreal * Xreal - Wimag * Ximag;
                            Yimag = Wreal * Ximag + Wimag * Xreal;

                            envs->array[iSep][iSampleB] += sqrtf(Yreal*Yreal + Yimag*Yimag);

                        }

                    }

                }

            }
            else {

                memset(envs->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize);

            }

        }        

    }
