
   /**
    * \file     env2env.c
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

    #include <system/env2env.h>

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

        obj->idsPrev = (unsigned long long *) malloc(sizeof(unsigned long long) * nChannels);
        memset(obj->idsPrev, 0x00, sizeof(unsigned long long) * nChannels);
        obj->l = (unsigned int *) malloc(sizeof(unsigned int) * nChannels);
        memset(obj->l, 0x00, sizeof(unsigned int) * nChannels);

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

        unsigned iChannel;

        free((void *) obj->idsPrev);
        free((void *) obj->l);
        free((void *) obj->b);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            free((void *) obj->Sf[iChannel]);
            free((void *) obj->S[iChannel]);
            free((void *) obj->SPrev[iChannel]);
            free((void *) obj->Smin[iChannel]);
            free((void *) obj->SminPrev[iChannel]);
            free((void *) obj->Stmp[iChannel]);
            free((void *) obj->StmpPrev[iChannel]);
            free((void *) obj->lambdaD[iChannel]);
            free((void *) obj->lambdaDnext[iChannel]);

        }

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
        signed int iBinWrapped;
        float sample;

        char doProcess;
        char doReset;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks != NULL) {

                if (tracks->ids[iChannel] != 0) {

                    if (obj->idsPrev[iChannel] != 0) {

                        doProcess = 0x01;
                        doReset = 0x00;

                    }
                    else {

                        doProcess = 0x01;
                        doReset = 0x01;

                    }

                }
                else {

                    doProcess = 0x00;
                    doReset = 0x00;

                }

                obj->idsPrev[iChannel] = tracks->ids[iChannel];

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

                        iBinWrapped = ((signed int) iBin) + iSample - ((signed int) ((obj->bSize-1)/2));

                        if (iBinWrapped < 0) {
                            iBinWrapped = -1 * iBinWrapped;
                        }
                        if (iBinWrapped >= ((signed int) obj->halfFrameSize)) {
                            iBinWrapped = 2*(obj->halfFrameSize-1) - iBinWrapped;
                        }

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

                    if ((obj->S[iChannel][iBin] < (obj->Smin[iChannel][iBin] * obj->delta)) || (obj->lambdaD[iChannel][iBin] > obj->S[iChannel][iBin])) {

                        obj->lambdaDnext[iChannel][iBin] = (1.0f - obj->alphaD) * obj->lambdaD[iChannel][iBin] + obj->alphaD * obj->S[iChannel][iBin];

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

    env2env_interf_obj * env2env_interf_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float eta, const float alphaZ) {

        env2env_interf_obj * obj;
        unsigned int iChannel;

        obj = (env2env_interf_obj *) malloc(sizeof(env2env_interf_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->eta = eta;
        obj->alphaZ = alphaZ;

        obj->Zs = (float **) malloc(sizeof(float *) * nChannels);
        obj->ZsPrev = (float **) malloc(sizeof(float *) * nChannels);

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            obj->Zs[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->Zs[iChannel], 0x00, sizeof(float) * halfFrameSize);
            obj->ZsPrev[iChannel] = (float *) malloc(sizeof(float) * halfFrameSize);
            memset(obj->ZsPrev[iChannel], 0x00, sizeof(float) * halfFrameSize);

        }

        return obj;

    }

    void env2env_interf_destroy(env2env_interf_obj * obj) {

        unsigned int iChannel;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            
            free((void *) obj->Zs[iChannel]);
            free((void *) obj->ZsPrev[iChannel]);

        }

        free((void *) obj->Zs);
        free((void *) obj->ZsPrev);

        free((void *) obj);

    }

    void env2env_interf_process(env2env_interf_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * noises, envs_obj * interfs) {

        unsigned int iChannel1;
        unsigned int iChannel2;
        unsigned int iChannel;
        unsigned int iBin;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks->ids[iChannel] != 0) {

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->Zs[iChannel][iBin] = (1.0f - obj->alphaZ) * obj->ZsPrev[iChannel][iBin] + obj->alphaZ * seps->array[iChannel][iBin];

                }

                memcpy(obj->ZsPrev[iChannel], obj->Zs[iChannel], sizeof(float)*obj->halfFrameSize);

            }
            else {

                memset(obj->Zs[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->ZsPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }

        }

        for (iChannel1 = 0; iChannel1 < obj->nChannels; iChannel1++) {

            if (tracks->ids[iChannel1] != 0) {

                memset(interfs->array[iChannel1], 0x00, sizeof(float) * obj->halfFrameSize);

                for (iChannel2 = 0; iChannel2 < obj->nChannels; iChannel2++) {

                    if (tracks->ids[iChannel2] != 0) {

                        if (iChannel1 != iChannel2) {

                            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                                interfs->array[iChannel1][iBin] += obj->Zs[iChannel2][iBin] * obj->eta;

                            }

                        }

                    }

                }

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    interfs->array[iChannel1][iBin] += noises->array[iChannel1][iBin];

                }                

            }
            else {

                memset(interfs->array[iChannel1], 0x00, sizeof(float) * obj->halfFrameSize);

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

    void env2env_gainspeech_process(env2env_gainspeech_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * noises, envs_obj * gains, envs_obj * snrs, envs_obj * vs) {

        unsigned int iChannel;
        unsigned int iBin;
        float xi_over_xi_plus_1;
        float max_gamma_minus_1_vs_0;
        float GH1_2;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks->ids[iChannel] != 0) {

                //
                // gamma_l[k] = |Y_l(k)|^2 / (lambda_l[k] + epsilon)
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->gamma[iChannel][iBin] = seps->array[iChannel][iBin] / (noises->array[iChannel][iBin] + obj->epsilon);

                }

                //
                // alphaP_l[k] = min{(xi_l-1[k] / (xi_l-1[k] + 1))^2 + alphaPmin, 1.0}
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    xi_over_xi_plus_1 = obj->xi[iChannel][iBin] / (obj->xi[iChannel][iBin] + 1.0f);

                    obj->alphaP[iChannel][iBin] = xi_over_xi_plus_1 * xi_over_xi_plus_1 + obj->alphaPmin;

                    if (obj->alphaP[iChannel][iBin] > 1.0f) {
                        obj->alphaP[iChannel][iBin] = 1.0f;
                    }

                }

                //
                // xi_l[k] = (1 - alphaP_l[k]) * (GH1_l-1[k])^2 * gamma_l[k] + alphaP_l[k] * max{gamma_l[k]-1,0}
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    if ((obj->gamma[iChannel][iBin] - 1.0f) < 0.0f) {
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
                // GH1_l[k] = (xi_l[k] / (xi_l[k] + 1)) * fcn(v_l[k])
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->GH1[iChannel][iBin] = (obj->xi[iChannel][iBin] / (obj->xi[iChannel][iBin] + 1.0f)) * transcendental_process(obj->transcendental, obj->v[iChannel][iBin]);

                    if (obj->GH1[iChannel][iBin] > 1.0f) {
                        obj->GH1[iChannel][iBin] = 1.0f;
                    }

                }

                memcpy(gains->array[iChannel],obj->GH1[iChannel],sizeof(float) * obj->halfFrameSize);
                memcpy(snrs->array[iChannel],obj->xi[iChannel],sizeof(float) * obj->halfFrameSize);
                memcpy(vs->array[iChannel],obj->v[iChannel],sizeof(float) * obj->halfFrameSize);

            }
            else {

                memset(obj->gamma[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->alphaP[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->xi[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->GH1[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->v[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

                memset(gains->array[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(snrs->array[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(vs->array[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }            

        }

    }

    env2env_probspeech_obj * env2env_probspeech_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float theta, const float alpha, const float maxAbsenceProb, const float Gmin, const unsigned int winSizeLocal, const unsigned int winSizeGlobal, const unsigned int winSizeFrame) {

        env2env_probspeech_obj * obj;
        unsigned int iSample;
        unsigned int iChannel;
        signed int iSampleShifted;
        unsigned int iSampleWrapped;
        float total;

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
            total = 0.0f;
            for ( iSample = 0; iSample < winSizeLocal; iSample++ ) {
                obj->winLocal[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) (iSample+1) ) / ( (float) ( (winSizeLocal+2) - 1 ) ) ) );
                total += obj->winLocal[iSample];
            }
            for ( iSample = 0; iSample < winSizeLocal; iSample++ ) {
                obj->winLocal[iSample] /= total;
            }
        }

        if ( winSizeGlobal == 1 ) {
            obj->winGlobal[0] = 1.0f;
        }
        else {
            total = 0.0f;
            for ( iSample = 0; iSample < winSizeGlobal; iSample++ ) {
                obj->winGlobal[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) (iSample+1) ) / ( (float) ( (winSizeGlobal+2) - 1 ) ) ) );
                total += obj->winGlobal[iSample];
            }
            for ( iSample = 0; iSample < winSizeGlobal; iSample++ ) {
                obj->winGlobal[iSample] /= total;
                
            }            
        }

        if ( winSizeFrame == 1 ) {
            obj->winFrame[0] = 1.0f;
        }
        else {
            total = 0.0f;
            for ( iSample = 0; iSample < winSizeFrame; iSample++ ) {
                obj->winFrame[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) (iSample+1) ) / ( (float) ( (winSizeFrame+2) - 1 ) ) ) );
                total += obj->winFrame[iSample];
            }
            for ( iSample = 0; iSample < winSizeFrame; iSample++ ) {
                obj->winFrame[iSample] /= total;
            }                 
        }        

        obj->winLocalShifted = (float *) malloc(sizeof(float) * obj->frameSize);
        memset(obj->winLocalShifted, 0x00, sizeof(float) * obj->frameSize);
        obj->winGlobalShifted = (float *) malloc(sizeof(float) * obj->frameSize);
        memset(obj->winGlobalShifted, 0x00, sizeof(float) * obj->frameSize);
        obj->winFrameShifted = (float *) malloc(sizeof(float) * obj->frameSize);
        memset(obj->winFrameShifted, 0x00, sizeof(float) * obj->frameSize);

        for (iSample = 0; iSample < obj->winSizeLocal; iSample++) {      

            iSampleShifted = iSample - (obj->winSizeLocal / 2);

            if (iSampleShifted < 0) {
                iSampleWrapped = (unsigned int) (iSampleShifted + obj->frameSize);
            }
            else {
                iSampleWrapped = (unsigned int) (iSampleShifted);   
            }

            obj->winLocalShifted[iSampleWrapped] = obj->winLocal[iSample];

        }

        for (iSample = 0; iSample < obj->winSizeGlobal; iSample++) {      

            iSampleShifted = iSample - (obj->winSizeGlobal / 2);

            if (iSampleShifted < 0) {
                iSampleWrapped = (unsigned int) (iSampleShifted + obj->frameSize);
            }
            else {
                iSampleWrapped = (unsigned int) (iSampleShifted);   
            }

            obj->winGlobalShifted[iSampleWrapped] = obj->winGlobal[iSample];

        }        

        for (iSample = 0; iSample < obj->winSizeFrame; iSample++) {      

            iSampleShifted = iSample - (obj->winSizeFrame / 2);

            if (iSampleShifted < 0) {
                iSampleWrapped = (unsigned int) (iSampleShifted + obj->frameSize);
            }
            else {
                iSampleWrapped = (unsigned int) (iSampleShifted);   
            }

            obj->winFrameShifted[iSampleWrapped] = obj->winFrame[iSample];

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

        obj->zetaLocal = (float **) malloc(sizeof(float *) * nChannels);
        obj->zetaLocalPrev = (float **) malloc(sizeof(float *) * nChannels);
        obj->zetaGlobal = (float **) malloc(sizeof(float *) * nChannels);
        obj->zetaGlobalPrev = (float **) malloc(sizeof(float *) * nChannels);
        obj->zetaFrame = (float **) malloc(sizeof(float *) * nChannels);
        obj->zetaFramePrev = (float **) malloc(sizeof(float *) * nChannels);

        obj->PLocal = (float **) malloc(sizeof(float *) * nChannels);
        obj->PGlobal = (float **) malloc(sizeof(float *) * nChannels);
        obj->PFrame = (float **) malloc(sizeof(float *) * nChannels);

        obj->q = (float **) malloc(sizeof(float *) * nChannels);
        obj->p = (float **) malloc(sizeof(float *) * nChannels);

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

            obj->zetaLocal[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->zetaLocal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->zetaLocalPrev[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->zetaLocalPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->zetaGlobal[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->zetaGlobal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->zetaGlobalPrev[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->zetaGlobalPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->zetaFrame[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->zetaFrame[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->zetaFramePrev[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->zetaFramePrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            obj->PLocal[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->PLocal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->PGlobal[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->PGlobal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->PFrame[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->PFrame[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            obj->q[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->q[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
            obj->p[iChannel] = (float *) malloc(sizeof(float) * obj->halfFrameSize);
            memset(obj->p[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

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

            free((void *) obj->zetaLocal[iChannel]);
            free((void *) obj->zetaLocalPrev[iChannel]);
            free((void *) obj->zetaGlobal[iChannel]);
            free((void *) obj->zetaGlobalPrev[iChannel]);
            free((void *) obj->zetaFrame[iChannel]);
            free((void *) obj->zetaFramePrev[iChannel]);

            free((void *) obj->PLocal[iChannel]);
            free((void *) obj->PGlobal[iChannel]);
            free((void *) obj->PFrame[iChannel]);

            free((void *) obj->q[iChannel]);
            free((void *) obj->p[iChannel]);

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

        free((void *) obj->zetaLocal);
        free((void *) obj->zetaLocalPrev);
        free((void *) obj->zetaGlobal);
        free((void *) obj->zetaGlobalPrev);
        free((void *) obj->zetaFrame);
        free((void *) obj->zetaFramePrev);

        free((void *) obj->PLocal);
        free((void *) obj->PGlobal);
        free((void *) obj->PFrame);

        free((void *) obj->q);
        free((void *) obj->p);

        free((void *) obj);

    }

    void env2env_probspeech_process(env2env_probspeech_obj * obj, const tracks_obj * tracks, const envs_obj * snrs, const envs_obj * vs, envs_obj * probspeechs) {

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

        float theta_zeta;
        float PLocalGlobalFrame;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks->ids[iChannel] != 0) {

                //
                // Circular convolution with local, global and frame windows
                //

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

                //
                // zeta_l(k) = (1 - alpha) * zeta_l-1(k) + alpha * xiSmoothed_l(k)
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->zetaLocal[iChannel][iBin] = (1.0f - obj->alpha) * obj->zetaLocalPrev[iChannel][iBin] + obj->alpha * obj->xiSmoothedLocal[iChannel][iBin];
                    obj->zetaGlobal[iChannel][iBin] = (1.0f - obj->alpha) * obj->zetaGlobalPrev[iChannel][iBin] + obj->alpha * obj->xiSmoothedGlobal[iChannel][iBin];
                    obj->zetaFrame[iChannel][iBin] = (1.0f - obj->alpha) * obj->zetaFramePrev[iChannel][iBin] + obj->alpha * obj->xiSmoothedFrame[iChannel][iBin];

                }        

                memcpy(obj->zetaLocalPrev[iChannel], obj->zetaLocal[iChannel], sizeof(float) * obj->halfFrameSize);
                memcpy(obj->zetaGlobalPrev[iChannel], obj->zetaGlobal[iChannel], sizeof(float) * obj->halfFrameSize);
                memcpy(obj->zetaFramePrev[iChannel], obj->zetaFrame[iChannel], sizeof(float) * obj->halfFrameSize);

                //
                // P_l(k) = 1 / (1 + (theta/zeta_l(k))^2)
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    theta_zeta = obj->theta/obj->zetaLocal[iChannel][iBin];
                    obj->PLocal[iChannel][iBin] = 1.0f / (1.0f + (theta_zeta*theta_zeta));

                    theta_zeta = obj->theta/obj->zetaGlobal[iChannel][iBin];
                    obj->PGlobal[iChannel][iBin] = 1.0f / (1.0f + (theta_zeta*theta_zeta));

                    theta_zeta = obj->theta/obj->zetaFrame[iChannel][iBin];
                    obj->PFrame[iChannel][iBin] = 1.0f / (1.0f + (theta_zeta*theta_zeta));

                }

                //
                // q_l(k) = min(1-Plocal_l(k)*Pglobal_l(k)*Pframe_l(k))
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    PLocalGlobalFrame = obj->PLocal[iChannel][iBin] * obj->PGlobal[iChannel][iBin] * obj->PFrame[iChannel][iBin];

                    if ((1.0f - PLocalGlobalFrame) > 0.9f) {
                        obj->q[iChannel][iBin] = 0.9;
                    }
                    else {
                        obj->q[iChannel][iBin] = 1.0f - PLocalGlobalFrame;
                    }

                }

                //
                // p_l(k) = (1 + (q_l(k) / (1 - q_l(k)) * (1 + xi_l(k)) * exp(-v_l(k)))
                //

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    obj->p[iChannel][iBin] = 1.0f / (1.0f + (obj->q[iChannel][iBin] / (1.0f - obj->q[iChannel][iBin])) * (1.0f + snrs->array[iChannel][iBin]) * expf(-1.0f * vs->array[iChannel][iBin]));

                }

                memcpy(probspeechs->array[iChannel],obj->p[iChannel],sizeof(float) * obj->halfFrameSize);

            }
            else {

                memset(obj->xiTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
                memset(obj->xiFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);

                memset(obj->xiSmoothedLocalFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);
                memset(obj->xiSmoothedGlobalFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);
                memset(obj->xiSmoothedFrameFreq[iChannel], 0x00, sizeof(float) * obj->halfFrameSize * 2);
                memset(obj->xiSmoothedLocalTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
                memset(obj->xiSmoothedGlobalTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
                memset(obj->xiSmoothedFrameTime[iChannel], 0x00, sizeof(float) * obj->frameSize);
                memset(obj->xiSmoothedLocalTime[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->xiSmoothedGlobalTime[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->xiSmoothedFrameTime[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

                memset(obj->zetaLocal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->zetaLocalPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->zetaGlobal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->zetaGlobalPrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->zetaFrame[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->zetaFramePrev[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

                memset(obj->PLocal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->PGlobal[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->PFrame[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

                memset(obj->q[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);
                memset(obj->p[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);                

                memset(probspeechs->array[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }
            
        }

    }

    env2env_gainall_obj * env2env_gainall_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float Gmin) {

        env2env_gainall_obj * obj;

        obj = (env2env_gainall_obj *) malloc(sizeof(env2env_gainall_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->Gmin = Gmin;

        return obj;

    }

    void env2env_gainall_destroy(env2env_gainall_obj * obj) {

        free((void *) obj);

    }

    void env2env_gainall_process(env2env_gainall_obj * obj, const tracks_obj * tracks, const envs_obj * gainspeeches, const envs_obj * probspeeches, envs_obj * gainalls) {

        unsigned int iChannel;
        unsigned int iBin;

        float expr1;
        float expr2;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks->ids[iChannel] != 0) {

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    expr1 = powf(gainspeeches->array[iChannel][iBin], probspeeches->array[iChannel][iBin]);
                    expr2 = powf(obj->Gmin, (1.0f - probspeeches->array[iChannel][iBin]));

                    gainalls->array[iChannel][iBin] = expr1 * expr2;

                }

            }
            else {

                memset(gainalls->array[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }

        }

    }

    env2env_gainratio_obj * env2env_gainratio_construct_zero(const unsigned int nInitChannels, const unsigned int nChannels, const unsigned int halfFrameSize, const float Gmin, const float Gmid, const float Gslope, const float epsilon) {

        env2env_gainratio_obj * obj;

        obj = (env2env_gainratio_obj *) malloc(sizeof(env2env_gainratio_obj));

        obj->nInitChannels = nInitChannels;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;
        obj->Gmin = Gmin;
        obj->Gmid = Gmid;
        obj->Gslope = Gslope;
        obj->epsilon = epsilon;

        return obj;        

    }

    void env2env_gainratio_destroy(env2env_gainratio_obj * obj) {

        free((void *) obj);

    }

    void env2env_gainratio_process(env2env_gainratio_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * diffuse, envs_obj * gainratio) {

        unsigned int iChannel;
        unsigned int iBin;

        float ratio;
        float sigmoid;
        float gain;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (tracks->ids[iChannel] != 0) {

                for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                    ratio = seps->array[iChannel][iBin] / (((float) obj->nInitChannels) * diffuse->array[iChannel][iBin] + obj->epsilon);

                    sigmoid = 1.0f / (1.0f + expf(-1.0f * obj->Gslope * (ratio - obj->Gmid)));

                    gain = obj->Gmin + (1.0f - obj->Gmin) * sigmoid;

                    gainratio->array[iChannel][iBin] = gain;

                }

            }
            else {

                memset(gainratio->array[iChannel], 0x00, sizeof(float) * obj->halfFrameSize);

            }

        }

    }
