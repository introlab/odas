    
    #include "steer2demixing.h"

    steer2demixing_ds_obj * steer2demixing_ds_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float epsilon) {

        steer2demixing_ds_obj * obj;

        obj = (steer2demixing_ds_obj *) malloc(sizeof(steer2demixing_ds_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->epsilon = epsilon;

        obj->gains2 = (float *) malloc(sizeof(float) * halfFrameSize);
        memset(obj->gains2, 0x00, sizeof(float) * halfFrameSize);

        return obj;

    }

    void steer2demixing_ds_destroy(steer2demixing_ds_obj * obj) {

        free((void *) obj->gains2);
        free((void *) obj);

    }

    void steer2demixing_ds_process(steer2demixing_ds_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, demixings_obj * demixings) {

        unsigned int iSep;
        unsigned int iChannel;
        unsigned int iBin;
        unsigned int iSampleSC;
        unsigned int iSampleBC;

        char mask;
        float Areal;
        float Aimag;
        float gain2;
        float Wreal;
        float Wimag;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                memset(obj->gains2, 0x00, sizeof(float) * obj->halfFrameSize);

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->gains2[iBin] = obj->epsilon;

                }

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleSC = iSep * obj->nChannels + iChannel;
                    mask = masks->array[iSampleSC];

                    if (mask == 1) {                   

                        for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                            iSampleBC = iBin * obj->nChannels + iChannel;

                            Areal = steers->array[iSep][iSampleBC * 2 + 0];
                            Aimag = steers->array[iSep][iSampleBC * 2 + 1];

                            gain2 = Areal * Areal + Aimag * Aimag;

                            obj->gains2[iBin] += gain2;

                        }

                    }

                }

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleSC = iSep * obj->nChannels + iChannel;
                    mask = masks->array[iSampleSC];

                    if (mask == 1) {

                        for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                            iSampleBC = iBin * obj->nChannels + iChannel;

                            Areal = steers->array[iSep][iSampleBC * 2 + 0];
                            Aimag = steers->array[iSep][iSampleBC * 2 + 1];

                            Wreal = Areal / obj->gains2[iBin];
                            Wimag = -1.0f * Aimag / obj->gains2[iBin];

                            demixings->array[iSep][iSampleBC * 2 + 0] = Wreal;
                            demixings->array[iSep][iSampleBC * 2 + 1] = Wimag;

                        }

                    }                    

                }

            }

        }

    }


    steer2demixing_gss_obj * steer2demixing_gss_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float mu, const float lambda) {

        steer2demixing_gss_obj * obj;
        unsigned int iSep;

        obj = (steer2demixing_gss_obj *) malloc(sizeof(steer2demixing_gss_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->mu = mu;
        obj->lambda = lambda;

        obj->X = cmatrix_construct_zero(nChannels, 1);
        obj->XH = cmatrix_construct_zero(1, nChannels);

        obj->Y = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->YH = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->Ryy = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->E = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->A = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->AH = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->Wn = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->Wnp1 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ1 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ2 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);

        for (iSep = 0; iSep < nSeps; iSep++) {

            obj->Y[iSep] = cmatrix_construct_zero((iSep+1), 1);
            obj->YH[iSep] = cmatrix_construct_zero(1, (iSep+1));
            obj->Ryy[iSep] = cmatrix_construct_zero((iSep+1), (iSep+1));
            obj->E[iSep] = cmatrix_construct_zero((iSep+1), (iSep+1));
            obj->A[iSep] = cmatrix_construct_zero(nChannels, (iSep+1));
            obj->AH[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->Wn[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->Wnp1[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->dJ1[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->dJ2[iSep] = cmatrix_construct_zero((iSep+1), nChannels);

        }

        return obj;

    }

    void steer2demixing_gss_destroy(steer2demixing_gss_obj * obj) {

        unsigned int iSep;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            cmatrix_destroy(obj->Y[iSep]);
            cmatrix_destroy(obj->YH[iSep]);
            cmatrix_destroy(obj->Ryy[iSep]);
            cmatrix_destroy(obj->E[iSep]);
            cmatrix_destroy(obj->A[iSep]);
            cmatrix_destroy(obj->AH[iSep]);
            cmatrix_destroy(obj->Wn[iSep]);
            cmatrix_destroy(obj->Wnp1[iSep]);
            cmatrix_destroy(obj->dJ1[iSep]);
            cmatrix_destroy(obj->dJ2[iSep]);

        }

        free((void *) obj->Y);
        free((void *) obj->YH);
        free((void *) obj->Ryy);
        free((void *) obj->E);
        free((void *) obj->A);
        free((void *) obj->AH);
        free((void *) obj->Wn);
        free((void *) obj->Wnp1);
        free((void *) obj->dJ1);
        free((void *) obj->dJ2);

        cmatrix_destroy(obj->XH);
        cmatrix_destroy(obj->X);

        free((void *) obj);

    }

    void steer2demixing_gss_process(steer2demixing_gss_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, demixings_obj * demixings) {

        unsigned int nActiveSeps;
        unsigned int iSep;
        unsigned int iBin;
        unsigned int iChannel;

        nActiveSeps = 0;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            nActiveSeps++;

        }


    }
    
    steer2demixing_mvdr_obj * steer2demixing_mvdr_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float sigma) {

    }

    void steer2demixing_mvdr_process(steer2demixing_mvdr_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, demixings_obj * demixings) {

    }

    void steer2demixing_mvdr_destroy(steer2demixing_mvdr_obj * obj) {

    }