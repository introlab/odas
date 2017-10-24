
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

        obj->l = 0;

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

        free((void *) obj);

    }

    void env2env_mcra_process(env2env_mcra_obj * obj, const envs_obj * noisy, envs_obj * noise) {

        unsigned int iChannel;
        unsigned int iBin;
        signed int iSample;
        unsigned int iBinWrapped;
        float sample;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            //           N-1
            //           +--
            // Sf_l[k] = >   b[n] |X_l[k+n-(N-1)/2]|^2
            //           +--
            //           n=0

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                sample = 0.0f;

                for (iSample = 0; iSample < obj->bSize; iSample++) {

                    iBinWrapped = (unsigned int) abs(((signed int) iBin) + iSample - ((obj->bSize-1)/2));
                    sample += obj->b[iSample] * noisy->array[iChannel][iBinWrapped];

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

            if (obj->l < obj->L) {

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

            }

            //                                                                  \
            //                                                                  | S_l[k] < Smin_l[k] * delta
            // lambdaD_l+1[k] = (1-alphaD) * lambdaD_l[k] + alphaD * |Y_l[k]|^2 | lambdaD_l[k] > |Y_l[k]|^2
            //                                                                  |
            //                                                                  / 
            //
            // lambdaD_l+1[k] = lambdaD_l[k]                                    otherwise
            //

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                if ((obj->S[iChannel][iBin] < (obj->Smin[iChannel][iBin] * obj->delta)) || (obj->lambdaD[iChannel][iBin] > noisy->array[iChannel][iBin])) {

                    obj->lambdaDnext[iChannel][iBin] = obj->lambdaD[iChannel][iBin];

                }

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

        // Count frames

        (obj->l)++;

        if (obj->l >= obj->L) {
            obj->l = 0;
        }

    }
