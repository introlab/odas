
    #include "env2env.h"

    env2env_mcra_obj * env2env_mcra_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const unsigned int bSize, const float alphaS, const unsigned int L, const float delta, const float alphaD) {

        env2env_mcra_obj * obj;
        unsigned int n;
        unsigned int iChannel;
        float bTotal;

        obj = (env2env_mcra_obj *) malloc(sizeof(env2env_mcra_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->bSize = bSize;
        obj->alphaS = alphaS;
        obj->L = L;
        obj->delta = delta;
        obj->alphaD = alphaD;

        obj->l = (unsigned int *) malloc(sizeof(unsigned int) * nChannels);
        memset(obj->l, 0x00, sizeof(unsigned int) * nChannels);
        obj->first = (char *) malloc(sizeof(char) * nChannels);
        memset(obj->first, 0x00, sizeof(char) * nChannels);

        obj->b = (float *) malloc(sizeof(float) * bSize);
        for (n = 0; n < obj->bSize; n++) {
            obj->b[n] = 0.5f * (1.0f * cosf(2.0f * M_PI * ((float) (n + 1)) / ((float) (obj->bSize + 1))));
            bTotal += (float) (obj->b[n]);
        }
        for (n = 0; n < obj->bSize; n++) {
            obj->b[n] /= bTotal;
        }

        obj->Sf = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->S = (float **) malloc(sizeof(float *) * obj->nChannels);        
        obj->SPrev = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->Smin = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->SminPrev = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->Stmp = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->StmpPrev = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->lambdaD = (float **) malloc(sizeof(float *) * obj->nChannels);
        obj->lambdaDnext = (float **) malloc(sizeof(float *) * obj->nChannels);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            obj->Sf[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->Sf[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->S[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->S[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->SPrev[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->SPrev[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->Smin[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->Smin[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->SminPrev[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->SminPrev[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->Stmp[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->Stmp[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->StmpPrev[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->StmpPrev[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->lambdaD[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->lambdaD[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->lambdaDnext[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->lambdaDnext[iChannel], 0x00, sizeof(float) * halfFrameSize);

        }

        return obj;

    }

    void env2env_mcra_destroy(env2env_mcra_obj * obj) {

        free((void *) obj->l);
        free((void *) obj->first);
        free((void *) obj->b);

        free((void *) obj->Sf);
        free((void *) obj->S);
        free((void *) obj->SPrev);
        free((void *) obj->Smin);
        free((void *) obj->SminPrev);
        free((void *) obj->Stmp);
        free((void *) obj->StmpPrev);
        free((void *) obj->lambdaD);
        free((void *) obj->lambdaDnext);

        free((void *) obj);

    }

    void env2env_mcra_process(env2env_mcra_obj * obj, const tracks_obj * tracks, const envs_obj * noisys, const envs_obj * estNoises, envs_obj * noises) {

        unsigned int iChannel;
        unsigned int iBin;
        signed int iSample;
        unsigned int iBinWrapped;
        float sample;

        char doProcess;
        char doReset;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks != NULL) {

                if (tracks->ids[iChannel] != 0) {

                    doProcess = 0x01;
                    doReset = 0x00;

                }
                else {

                    doProcess = 0x00;
                    doReset = 0x01;

                }

            }
            else {

                doProcess = 0x01;
                doReset = 0x00;

            }

            if (doReset == 0x01) {

                obj->l[iChannel] = 0; 

                if (estNoises != NULL) {

                    memcpy(obj->Sf[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->S[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->SPrev[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->Smin[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->SminPrev[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->Stmp[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->StmpPrev[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->lambdaD[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);
                    memcpy(obj->lambdaDnext[iChannel], estNoises->array[iChannel], sizeof(float) * obj->halfFrameSize);

                    obj->first[iChannel] = 0x00;

                }
                else {

                    memset(obj->Sf[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->S[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->SPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->Smin[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->SminPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->Stmp[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->StmpPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->lambdaD[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                    memset(obj->lambdaDnext[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

                    obj->first[iChannel] = 0x01;

                }

            }

            if (doProcess == 0x01) {

                //           N-1
                //           +--
                // Sf_l[k] = >   b[n] |X_l[k+n-(N-1)/2]|^2
                //           +--
                //           n=0

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    sample = 0.0f;

                    for (iSample = 0; iSample < obj->bSize; iSample++) {

                        iBinWrapped = (unsigned int) abs(((signed int) iBin) + iSample - ((obj->bSize-1)/2));
                        sample += obj->b[iSample] * noisys->array[iChannel][iBinWrapped];

                    }

                    obj->Sf[iChannel][iBin] = sample;

                }

                //
                // S_l[k] = (1 - alphaS) * S_l-1[k] + alphaS * Sf_l[k]
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->S[iChannel][iBin] = (1 - obj->alphaS) * obj->SPrev[iChannel][iBin] + obj->alphaS * obj->Sf[iChannel][iBin];

                }

                //                                     \
                // Smin_l[k] = min{Smin_l-1[k],S_l[k]} | l < L 
                // Stmp_l[k] = min{Stmp_l-1[k],S_l[k]} |
                //                                     / 
                //                                     \
                // Smin_l[k] = min{Stmp_l-1[k],S_l[k]} | l = L
                // Stmp_l[k] = S_l[k]                  |
                //                                     /

                if (obj->l[iChannel] <= obj->L) {

                    // Smin_l[k] = min{Smin_l-1[k],S_l[k]}
                    // Stmp_l[k] = min{Stmp_l-1[k],S_l[k]}

                    for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                        if (obj->SminPrev[iChannel][iBin] < obj->S[iChannel][iBin]) {
                            obj->Smin[iChannel][iBin] = obj->SminPrev[iChannel][iBin];
                        }
                        else {
                            obj->Smin[iChannel][iBin] = obj->S[iChannel][iBin];
                        }

                        if (obj->StmpPrev[iChannel][iBin] < obj->S[iChannel][iBin]) {
                            obj->Stmp[iChannel][iBin] = obj->StmpPrev[iChannel][iBin];
                        }
                        else {
                            obj->Stmp[iChannel][iBin] = obj->S[iChannel][iBin];
                        }

                    }

                    // Count frames

                    (obj->l[iChannel])++;       

                }
                else {

                    // Smin_l[k] = min{Stmp_l-1[k],S_l[k]}
                    // Stmp_l[k] = S_l[k]

                    for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                        if (obj->StmpPrev[iChannel][iBin] < obj->S[iChannel][iBin]) {
                            obj->Smin[iChannel][iBin] = obj->StmpPrev[iChannel][iBin];
                        }
                        else {
                            obj->Smin[iChannel][iBin] = obj->S[iChannel][iBin];
                        }

                        obj->Stmp[iChannel][iBin] = obj->S[iChannel][iBin];

                    }

                    // Reset frame counter

                    obj->l[iChannel] = 0;
                    obj->first[iChannel] = 0x00;

                }

                //                                                                  \
                //                                                                  | S_l[k] < Smin_l[k] * delta
                // lambdaD_l+1[k] = (1-alphaD) * lambdaD_l[k] + alphaD * |Y_l[k]|^2 | lambdaD_l[k] > |Y_l[k]|^2
                //                                                                  |
                //                                                                  / 
                //
                // lambdaD_l+1[k] = lambdaD_l[k]                                    otherwise
                //

                if (obj->first[iChannel] = 0x00) {

                    for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                        if ((obj->S[iChannel][iBin] < (obj->Smin[iChannel][iBin] * obj->delta)) || (obj->lambdaD[iChannel][iBin] > obj->S[iChannel][iBin])) {

                            obj->lambdaDnext[iChannel][iBin] = (1.0f - obj->alphaD) * obj->lambdaD[iChannel][iBin] + obj->alphaD * obj->S[iChannel][iBin];

                        }

                    }

                }
                else {

                    for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                        obj->lambdaDnext[iChannel][iBin] = (1.0f - obj->alphaD) * obj->lambdaD[iChannel][iBin] + obj->alphaD * obj->S[iChannel][iBin];
                        obj->StmpPrev[iChannel][iBin] = obj->lambdaDnext[iChannel][iBin];

                    }

                }

                // Copy to output

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    noises->array[iChannel][iBin] = obj->lambdaDnext[iChannel][iBin];

                }

                // Smin_l-1 = Smin_l
                // S_l-1 = S_l
                // Stmp_l-1 = Stmp_l
                // lambdaD_l = lambdaD_l+1

                memcpy(obj->SminPrev[iChannel], obj->Smin[iChannel], sizeof(float) * obj->halfFrameSize);
                memcpy(obj->SPrev[iChannel], obj->S[iChannel], sizeof(float) * obj->halfFrameSize);
                memcpy(obj->StmpPrev[iChannel], obj->Stmp[iChannel], sizeof(float) * obj->halfFrameSize);
                memcpy(obj->lambdaD[iChannel], obj->lambdaDnext[iChannel], sizeof(float) * obj->halfFrameSize);

            }

        }

    }

    env2env_weight_obj * env2env_weight_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float alphaD, const float epsilon) {

        env2env_weight_obj * obj;
        unsigned int iChannel;

        obj = (env2env_weight_obj *) malloc(sizeof(env2env_weight_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->alphaD = alphaD;
        obj->epsilon = epsilon;

        obj->XPrev = (float **) malloc(sizeof(float *) * nChannels);
        obj->xi = (float **) malloc(sizeof(float *) * nChannels);
        obj->zetaPrev = (float **) malloc(sizeof(float *) * nChannels);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            obj->XPrev[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->XPrev[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->xi[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->xi[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->zetaPrev[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->zetaPrev[iChannel], 0x00, sizeof(float) * halfFrameSize);

        }

        return obj;

    }

    void env2env_weight_destroy(env2env_weight_obj * obj) {

        unsigned int iChannel;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            free((void *) obj->XPrev[iChannel]);
            free((void *) obj->xi[iChannel]);
            free((void *) obj->zetaPrev[iChannel]);

        }

        free((void *) obj->XPrev);
        free((void *) obj->xi);
        free((void *) obj->zetaPrev);

    }

    void env2env_weight_process(env2env_weight_obj * obj, const tracks_obj * tracks, const envs_obj * noisys, const envs_obj * noises, envs_obj * weights) {

        unsigned int iChannel;
        unsigned int iBin;

        char doProcess;
        char doReset;        

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks != NULL) {

                if (tracks->ids[iChannel] != 0) {

                    doProcess = 0x01;
                    doReset = 0x00;

                }
                else {

                    doProcess = 0x00;
                    doReset = 0x01;

                }

            }
            else {

                doProcess = 0x01;
                doReset = 0x00;

            }

            if (doReset == 0x01) {

                memset(obj->XPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->xi[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->zetaPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }

            if (doProcess == 0x01) {

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->xi[iChannel][iBin] = ((1 - obj->alphaD) * obj->zetaPrev[iChannel][iBin] * obj->XPrev[iChannel][iBin] + obj->alphaD * noisys->array[iChannel][iBin]) / (noises->array[iChannel][iBin] + obj->epsilon);
                    weights->array[iChannel][iBin] = obj->xi[iChannel][iBin] / (obj->xi[iChannel][iBin] + 1.0f);

                    obj->XPrev[iChannel][iBin] = noisys->array[iChannel][iBin];
                    obj->zetaPrev[iChannel][iBin] = weights->array[iChannel][iBin];

                }                

            }

        }

    }

    env2env_interf_obj * env2env_interf_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float eta) {

        env2env_interf_obj * obj;

        obj = (env2env_interf_obj *) malloc(sizeof(env2env_interf_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->eta = eta;

        return obj;

    }

    void env2env_interf_destroy(env2env_interf_obj * obj) {

        free((void *) obj);

    }

    void env2env_interf_process(env2env_interf_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * noises, envs_obj * interfs) {

        unsigned int iChannel1;
        unsigned int iChannel2;
        unsigned int iBin;

        for (iChannel1 = 0; iChannel1 < obj->nChannels; iChannel1++) {

            if (tracks->ids[iChannel1] != 0) {

                memset(interfs->array[iChannel1], 0x00, sizeof(float) * obj->halfFrameSize);

                for (iChannel2 = 0; iChannel2 < obj->nChannels; iChannel2++) {

                    if (tracks->ids[iChannel2] != 0) {

                        if (iChannel1 != iChannel2) {

                            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                                interfs->array[iChannel1][iBin] += seps->array[iChannel2][iBin] * obj->eta;

                            }

                        }

                    }

                }

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    interfs->array[iChannel1][iBin] += noises->array[iChannel1][iBin];

                }                

            }

        }

    }

    env2env_gainspeech_obj * env2env_gainspeech_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float alphaPmin, const float epsilon) {

        env2env_gainspeech_obj * obj;
        unsigned int iChannel;

        obj = (env2env_gainspeech_obj *) malloc(sizeof(env2env_gainspeech_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->alphaPmin = alphaPmin;
        obj->epsilon = epsilon;

        obj->gamma = (float **) malloc(sizeof(float *) * nChannels);
        obj->alphaP = (float **) malloc(sizeof(float *) * nChannels);
        obj->xi = (float **) malloc(sizeof(float *) * nChannels);
        obj->GH1 = (float **) malloc(sizeof(float *) * nChannels);
        obj->v = (float **) malloc(sizeof(float *) * nChannels);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            obj->gamma[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->gamma[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->alphaP[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->alphaP[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->xi[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->xi[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->GH1[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->GH1[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->v[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->v[iChannel], 0x00, sizeof(float) * halfFrameSize);

        }

        obj->transcendental = transcendental_construct_zero(0.0f, 5.0f, 5001);

        return obj;

    }

    void env2env_gainspeech_destroy(env2env_gainspeech_obj * obj) {

        unsigned int iChannel;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            free((void *) obj->gamma[iChannel]);
            free((void *) obj->alphaP[iChannel]);
            free((void *) obj->xi[iChannel]);
            free((void *) obj->GH1[iChannel]);
            free((void *) obj->v[iChannel]);

        }

        free((void *) obj->gamma);
        free((void *) obj->alphaP);
        free((void *) obj->xi);
        free((void *) obj->GH1);
        free((void *) obj->v);

        transcendental_destroy(obj->transcendental);

        free((void *) obj);

    }

    void env2env_gainspeech_process(env2env_gainspeech_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * noises, envs_obj * gains, envs_obj * snrs) {

        unsigned int iChannel;
        unsigned int iBin;
        float xi_plus_1;
        float max_gamma_minus_1_vs_0;
        float GH1_2;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks->ids[iChannel] != 0) {

                memset(obj->gamma[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->alphaP[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->xi[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->GH1[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->v[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }
            else {

                //
                // gamma_l[k] = |Y_l(k)|^2 / (lambda_l[k] + epsilon)
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->gamma[iChannel][iBin] = seps->array[iChannel][iBin] / (noises->array[iChannel][iBin] + obj->epsilon);

                }

                //
                // alphaP_l[k] = (xi_l-1[k] / (xi_l-1[k] + 1)^2) + alphaPmin
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    xi_plus_1 = obj->xi[iChannel][iBin] + 1;

                    obj->alphaP[iChannel][iBin] = obj->xi[iChannel][iBin] / (xi_plus_1*xi_plus_1) + obj->alphaPmin;

                }

                //
                // xi_l[k] = (1 - alphaP_l[k]) * (GH1_l-1[k])^2 * gamma_l[k] + alphaP_l[k] * max{gamma_l[k]-1,0}
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    if ((obj->gamma[iChannel][iBin] - 1.0f) > 0.0f) {
                        max_gamma_minus_1_vs_0 = 0.0f;
                    }
                    else {
                        max_gamma_minus_1_vs_0 = obj->gamma[iChannel][iBin] - 1.0f;
                    }

                    GH1_2 = obj->GH1[iChannel][iBin] * obj->GH1[iChannel][iBin];

                    obj->xi[iChannel][iBin] = (1.0f - obj->alphaP[iChannel][iBin]) * GH1_2 * obj->gamma[iChannel][iBin] + obj->alphaP[iChannel][iBin] * max_gamma_minus_1_vs_0;

                }

                //
                // v_l[k] = gamma_l[k] * xi_l[k] / (xi_l[k] + 1)
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->v[iChannel][iBin] = obj->gamma[iChannel][iBin] * obj->xi[iChannel][iBin] / (obj->xi[iChannel][iBin] + 1.0f);

                }

                //
                // GH1_l[k] = fcn(v_l[k])
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->GH1[iChannel][iBin] = transcendental_process(obj->transcendental, obj->v[iChannel][iBin]);

                }

            }

        }

    }

    env2env_probspeech_obj * env2env_probspeech_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float theta, const float alpha, const float maxAbsenceProb, const float Gmin, const unsigned int winSizeLocal, const unsigned int winSizeGlobal, const unsigned int winSizeFrame) {

        env2env_probspeech_obj * obj;
        unsigned int iSample;
        unsigned int iChannel;

        obj = (env2env_probspeech_obj *) malloc(sizeof(env2env_probspeech_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->frameSize = (halfFrameSize-1) * 2;
        obj->theta = theta;
        obj->alpha = alpha;
        obj->maxAbsenceProb = maxAbsenceProb;
        obj->Gmin = Gmin;
        obj->winSizeLocal = winSizeLocal;
        obj->winSizeGlobal = winSizeGlobal;
        obj->winSizeFrame = winSizeFrame;

        obj->fft = fft_construct(obj->frameSize);

        obj->winLocal = (float *) malloc(sizeof(float) * winSizeLocal);
        memset(obj->winLocal, 0x00, sizeof(float) * winSizeLocal);
        obj->winGlobal = (float *) malloc(sizeof(float) * winSizeGlobal);
        memset(obj->winGlobal, 0x00, sizeof(float) * winSizeGlobal);
        obj->winFrame = (float *) malloc(sizeof(float) * winSizeFrame);
        memset(obj->winFrame, 0x00, sizeof(float) * winSizeFrame);

        if ( winSizeLocal == 1 ) {
            obj->winLocal[0] = 1.0f;
        }
        else {
            for ( iSample = 0; iSample < winSizeLocal; iSample++ ) {
                obj->winLocal[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( winSizeLocal - 1 ) ) ) );
            }
        }

        if ( winSizeGlobal == 1 ) {
            obj->winGlobal[0] = 1.0f;
        }
        else {
            for ( iSample = 0; iSample < winSizeGlobal; iSample++ ) {
                obj->winGlobal[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( winSizeGlobal - 1 ) ) ) );
            }
        }

        if ( winSizeFrame == 1 ) {
            obj->winFrame[0] = 1.0f;
        }
        else {
            for ( iSample = 0; iSample < winSizeFrame; iSample++ ) {
                obj->winFrame[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( winSizeFrame - 1 ) ) ) );
            }
        }        

        obj->winLocalShifted = (float *) malloc(sizeof(float) * obj->frameSize);
        memset(obj->winLocalShifted, 0x00, sizeof(float) * obj->frameSize);
        obj->winGlobalShifted = (float *) malloc(sizeof(float) * obj->frameSize);
        memset(obj->winGlobalShifted, 0x00, sizeof(float) * obj->frameSize);
        obj->winFrameShifted = (float *) malloc(sizeof(float) * obj->frameSize);
        memset(obj->winFrameShifted, 0x00, sizeof(float) * obj->frameSize);

        obj->winLocalShifted[0] = obj->winLocal[0];
        for (iSample = 1; iSample < obj->winSizeLocal; iSample++) {          
            obj->winLocalShifted[iSample] = obj->winLocal[iSample];
            obj->winLocalShifted[obj->frameSize-iSample] = obj->winLocal[iSample];
        }
        obj->winGlobalShifted[0] = obj->winGlobal[0];
        for (iSample = 1; iSample < obj->winSizeGlobal; iSample++) {          
            obj->winGlobalShifted[iSample] = obj->winGlobal[iSample];
            obj->winGlobalShifted[obj->frameSize-iSample] = obj->winGlobal[iSample];
        }
        obj->winFrameShifted[0] = obj->winFrame[0];
        for (iSample = 1; iSample < obj->winSizeFrame; iSample++) {          
            obj->winFrameShifted[iSample] = obj->winFrame[iSample];
            obj->winFrameShifted[obj->frameSize-iSample] = obj->winFrame[iSample];
        }

        obj->winLocalShiftedFreq = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
        memset(obj->winLocalShiftedFreq, 0x00, sizeof(float) * obj->halfFrameSize * 2);
        obj->winGlobalShiftedFreq = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
        memset(obj->winGlobalShiftedFreq, 0x00, sizeof(float) * obj->halfFrameSize * 2);
        obj->winFrameShiftedFreq = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
        memset(obj->winFrameShiftedFreq, 0x00, sizeof(float) * obj->halfFrameSize * 2);

        fft_r2c(obj->fft, obj->winLocalShifted, obj->winLocalShiftedFreq);
        fft_r2c(obj->fft, obj->winGlobalShifted, obj->winGlobalShiftedFreq);
        fft_r2c(obj->fft, obj->winFrameShifted, obj->winFrameShiftedFreq);

        obj->xiTime = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiFreq = (float **) malloc(sizeof(float *) * nChannels);

        obj->xiSmoothedLocalFreq = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedGlobalFreq = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedFrameFreq = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedLocalTime = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedGlobalTime = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedFrameTime = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedLocal = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedGlobal = (float **) malloc(sizeof(float *) * nChannels);
        obj->xiSmoothedFrame = (float **) malloc(sizeof(float *) * nChannels);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            obj->xiTime[iChannel] = (float *) malloc(sizeof(float) * obj->frameSize);
            memset(obj->xiTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
            obj->xiFreq[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
            memset(obj->xiFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);

            obj->xiSmoothedLocalFreq[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
            memset(obj->xiSmoothedLocalFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);
            obj->xiSmoothedGlobalFreq[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
            memset(obj->xiSmoothedGlobalFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);
            obj->xiSmoothedFrameFreq[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
            memset(obj->xiSmoothedFrameFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);
            obj->xiSmoothedLocalTime[iChannel] = (float *) malloc(sizeof(float) * obj->frameSize);
            memset(obj->xiSmoothedLocalTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
            obj->xiSmoothedGlobalTime[iChannel] = (float *) malloc(sizeof(float) * obj->frameSize);
            memset(obj->xiSmoothedGlobalTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
            obj->xiSmoothedFrameTime[iChannel] = (float *) malloc(sizeof(float) * obj->frameSize);
            memset(obj->xiSmoothedFrameTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
            obj->xiSmoothedLocal[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->xiSmoothedLocalTime[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->xiSmoothedGlobal[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->xiSmoothedGlobalTime[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->xiSmoothedFrame[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->xiSmoothedFrameTime[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

        }

        return obj;

    }

    void env2env_probspeech_destroy(env2env_probspeech_obj * obj) {

        unsigned int iChannel;

        fft_destroy(obj->fft);

        free((void *) obj->winLocal);
        free((void *) obj->winGlobal);
        free((void *) obj->winFrame);

        free((void *) obj->winLocalShifted);
        free((void *) obj->winGlobalShifted);
        free((void *) obj->winFrameShifted);

        free((void *) obj->winLocalShiftedFreq);
        free((void *) obj->winGlobalShiftedFreq);
        free((void *) obj->winFrameShiftedFreq);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            free((void *) obj->xiTime[iChannel]);
            free((void *) obj->xiFreq[iChannel]);

            free((void *) obj->xiSmoothedLocalFreq[iChannel]);
            free((void *) obj->xiSmoothedGlobalFreq[iChannel]);
            free((void *) obj->xiSmoothedFrameFreq[iChannel]);
            free((void *) obj->xiSmoothedLocalTime[iChannel]);
            free((void *) obj->xiSmoothedGlobalTime[iChannel]);
            free((void *) obj->xiSmoothedFrameTime[iChannel]);
            free((void *) obj->xiSmoothedLocal[iChannel]);
            free((void *) obj->xiSmoothedGlobal[iChannel]);
            free((void *) obj->xiSmoothedFrame[iChannel]);

        }

        free((void *) obj->xiTime);
        free((void *) obj->xiFreq);

        free((void *) obj->xiSmoothedLocalFreq);
        free((void *) obj->xiSmoothedGlobalFreq);
        free((void *) obj->xiSmoothedFrameFreq);
        free((void *) obj->xiSmoothedLocalTime);
        free((void *) obj->xiSmoothedGlobalTime);
        free((void *) obj->xiSmoothedFrameTime);
        free((void *) obj->xiSmoothedLocal);
        free((void *) obj->xiSmoothedGlobal);
        free((void *) obj->xiSmoothedFrame);

    }

    void env2env_probspeech_process(env2env_probspeech_obj * obj, const envs_obj * snrs, envs_obj * probspeechs) {

        unsigned int iChannel;
        unsigned int iBin;
        
        float hLocalReal;
        float hLocalImag;
        float hGlobalReal;
        float hGlobalImag;
        float hFrameReal;
        float hFrameImag;
        float xiReal;
        float xiImag;

        float hLocalxiReal;
        float hLocalxiImag;
        float hGlobalxiReal;
        float hGlobalxiImag;
        float hFramexiReal;
        float hFramexiImag;

        //
        // Circular convolution with local, global and frame windows
        //

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            obj->xiTime[iChannel][0] = snrs->array[iChannel][0];
            obj->xiTime[iChannel][obj->halfFrameSize-1] = snrs->array[iChannel][obj->halfFrameSize-1];

            for (iBin = 1; iBin < (obj->halfFrameSize-1); iBin++) {

                obj->xiTime[iChannel][iBin] = snrs->array[iChannel][iBin];
                obj->xiTime[iChannel][obj->frameSize-iBin] = snrs->array[iChannel][iBin];

            }

            fft_r2c(obj->fft, obj->xiTime[iChannel], obj->xiFreq[iChannel]);

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                hLocalReal = obj->winLocalShiftedFreq[iBin*2+0];
                hLocalImag = obj->winLocalShiftedFreq[iBin*2+1];
                hGlobalReal = obj->winGlobalShiftedFreq[iBin*2+0];
                hGlobalImag = obj->winGlobalShiftedFreq[iBin*2+1];
                hFrameReal = obj->winFrameShiftedFreq[iBin*2+0];
                hFrameImag = obj->winFrameShiftedFreq[iBin*2+1];
                xiReal = obj->xiFreq[iChannel][iBin*2+0];
                xiImag = obj->xiFreq[iChannel][iBin*2+1];

                hLocalxiReal = hLocalReal * xiReal - hLocalImag * xiImag;
                hLocalxiImag = hLocalReal * xiImag + hLocalImag * xiReal;
                hGlobalxiReal = hGlobalReal * xiReal - hGlobalImag * xiImag;
                hGlobalxiImag = hGlobalReal * xiImag + hGlobalImag * xiReal;
                hFramexiReal = hFrameReal * xiReal - hFrameImag * xiImag;
                hFramexiImag = hFrameReal * xiImag + hFrameImag * xiReal;

                obj->xiSmoothedLocalFreq[iChannel][iBin*2+0] = hLocalxiReal;
                obj->xiSmoothedLocalFreq[iChannel][iBin*2+1] = hLocalxiImag;
                obj->xiSmoothedGlobalFreq[iChannel][iBin*2+0] = hGlobalxiReal;
                obj->xiSmoothedGlobalFreq[iChannel][iBin*2+1] = hGlobalxiImag;
                obj->xiSmoothedFrameFreq[iChannel][iBin*2+0] = hFramexiReal;
                obj->xiSmoothedFrameFreq[iChannel][iBin*2+1] = hFramexiImag;

            }

            fft_c2r(obj->fft, obj->xiSmoothedLocalFreq[iChannel], obj->xiSmoothedLocalTime[iChannel]);
            fft_c2r(obj->fft, obj->xiSmoothedGlobalFreq[iChannel], obj->xiSmoothedGlobalTime[iChannel]);
            fft_c2r(obj->fft, obj->xiSmoothedFrameFreq[iChannel], obj->xiSmoothedFrameTime[iChannel]);

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                obj->xiSmoothedLocal[iChannel][iBin] = obj->xiSmoothedLocalTime[iChannel][iBin];
                obj->xiSmoothedGlobal[iChannel][iBin] = obj->xiSmoothedGlobalTime[iChannel][iBin];
                obj->xiSmoothedFrame[iChannel][iBin] = obj->xiSmoothedFrameTime[iChannel][iBin];

            }            

        }

    }