
   /**
    * \file     steer2demixing.c
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
    
    #include <system/steer2demixing.h>

    int count = 0;

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
                    else {

                        demixings->array[iSep][iSampleBC * 2 + 0] = 0.0f;
                        demixings->array[iSep][iSampleBC * 2 + 1] = 0.0f;

                    }             

                }

            }

        }

    }


    steer2demixing_gss_obj * steer2demixing_gss_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float mu, const float lambda, const float epsilon) {

        steer2demixing_gss_obj * obj;
        unsigned int iSep;

        obj = (steer2demixing_gss_obj *) malloc(sizeof(steer2demixing_gss_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->mu = mu;
        obj->lambda = lambda;
        obj->epsilon = epsilon;

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

        obj->dJ1_EY = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ1_4EY = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ1_4EYXH = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);

        obj->dJ2_WA = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ2_WAmI = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ2_2WAmI = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->dJ2_2WAmIAH = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);

        obj->alpha_dJ1 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->alpha_dJ1_p_dJ2 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->mu_alpha_dJ1_p_dJ2 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->one_m_lambda_mu_Wn = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);
        obj->one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2 = (cmatrix_obj **) malloc(sizeof(cmatrix_obj *) * nSeps);

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

            obj->dJ1_EY[iSep] = cmatrix_construct_zero((iSep+1), 1);
            obj->dJ1_4EY[iSep] = cmatrix_construct_zero((iSep+1), 1);
            obj->dJ1_4EYXH[iSep] = cmatrix_construct_zero((iSep+1), nChannels);

            obj->dJ2_WA[iSep] = cmatrix_construct_zero((iSep+1), (iSep+1));
            obj->dJ2_WAmI[iSep] = cmatrix_construct_zero((iSep+1), (iSep+1));
            obj->dJ2_2WAmI[iSep] = cmatrix_construct_zero((iSep+1), (iSep+1));
            obj->dJ2_2WAmIAH[iSep] = cmatrix_construct_zero((iSep+1), nChannels);

            obj->alpha_dJ1[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->alpha_dJ1_p_dJ2[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->mu_alpha_dJ1_p_dJ2[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->one_m_lambda_mu_Wn[iSep] = cmatrix_construct_zero((iSep+1), nChannels);
            obj->one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2[iSep] = cmatrix_construct_zero((iSep+1), nChannels);

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

            cmatrix_destroy(obj->dJ1_EY[iSep]);
            cmatrix_destroy(obj->dJ1_4EY[iSep]);
            cmatrix_destroy(obj->dJ1_4EYXH[iSep]);

            cmatrix_destroy(obj->dJ2_WA[iSep]);
            cmatrix_destroy(obj->dJ2_WAmI[iSep]);
            cmatrix_destroy(obj->dJ2_2WAmI[iSep]);
            cmatrix_destroy(obj->dJ2_2WAmIAH[iSep]);

            cmatrix_destroy(obj->alpha_dJ1[iSep]);
            cmatrix_destroy(obj->alpha_dJ1_p_dJ2[iSep]);
            cmatrix_destroy(obj->mu_alpha_dJ1_p_dJ2[iSep]);
            cmatrix_destroy(obj->one_m_lambda_mu_Wn[iSep]);
            cmatrix_destroy(obj->one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2[iSep]);

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

        free((void *) obj->dJ1_EY);
        free((void *) obj->dJ1_4EY);
        free((void *) obj->dJ1_4EYXH);

        free((void *) obj->dJ2_WA);
        free((void *) obj->dJ2_WAmI);
        free((void *) obj->dJ2_2WAmI);
        free((void *) obj->dJ2_2WAmIAH);

        free((void *) obj->alpha_dJ1);
        free((void *) obj->alpha_dJ1_p_dJ2);
        free((void *) obj->mu_alpha_dJ1_p_dJ2);
        free((void *) obj->one_m_lambda_mu_Wn);
        free((void *) obj->one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2);

        cmatrix_destroy(obj->XH);
        cmatrix_destroy(obj->X);

        free((void *) obj);

    }

    void steer2demixing_gss_process(steer2demixing_gss_obj * obj, const tracks_obj * tracksPrev, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, const demixings_obj * demixingsPrev, demixings_obj * demixings) {

        unsigned int iSep;
        unsigned int iBin;
        unsigned int iChannel;
        unsigned int nActiveSources;
        unsigned int iActiveSource;
        unsigned int iSampleSC;
        unsigned int iSampleBC;    
        unsigned int iSampleAC; 
        unsigned int iSampleCA;   

        float Areal;
        float Aimag;
        float Wreal;
        float Wimag;
        float gain2;
        float Xreal;
        float Ximag;
        float X2;
        float Rxx2;
        float alpha;

        nActiveSources = 0;

        // Count the number of active sources

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {
                
                nActiveSources++;

            }

        }

        //freqs_printf(freqs);

        if (nActiveSources > 0) {

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                //
                // Compute X[k] and X^H[k]
                //

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleBC = iBin * obj->nChannels + iChannel;

                    obj->X->real[iChannel] = freqs->array[iChannel][iBin*2+0];
                    obj->X->imag[iChannel] = freqs->array[iChannel][iBin*2+1];
                    obj->XH->real[iChannel] = freqs->array[iChannel][iBin*2+0];
                    obj->XH->imag[iChannel] = -1.0f * freqs->array[iChannel][iBin*2+1];

                }

                // 
                // Compute W_n[k], and add new sources is needed
                //

                iActiveSource = 0;

                cmatrix_zero(obj->Wn[nActiveSources-1]);

                for (iSep = 0; iSep < obj->nSeps; iSep++) {

                    if (tracks->ids[iSep] != 0) {

                        if (tracks->ids[iSep] == tracksPrev->ids[iSep]) {

                            // If the source was previously active, load the corresponding demixing terms

                            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                                iSampleBC = iBin * obj->nChannels + iChannel;
                                iSampleAC = iActiveSource * obj->nChannels + iChannel;

                                Wreal = demixingsPrev->array[iSep][iSampleBC * 2 + 0];
                                Wimag = demixingsPrev->array[iSep][iSampleBC * 2 + 1];

                                obj->Wn[nActiveSources-1]->real[iSampleAC] = Wreal;
                                obj->Wn[nActiveSources-1]->imag[iSampleAC] = Wimag;

                            }

                        }
                        else {

                            // Otherwise instantiate with terms of a weighted delay and sum beamformer
                            
                            gain2 = obj->epsilon;

                            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                                iSampleBC = iBin * obj->nChannels + iChannel;
                                iSampleSC = iSep * obj->nChannels + iChannel;
                                iSampleAC = iActiveSource * obj->nChannels + iChannel;

                                if (masks->array[iSampleSC] == 1) {

                                    Areal = steers->array[iSep][iSampleBC * 2 + 0];
                                    Aimag = steers->array[iSep][iSampleBC * 2 + 1];

                                    gain2 += Areal * Areal + Aimag * Aimag;

                                }

                            }

                            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                                iSampleBC = iBin * obj->nChannels + iChannel;
                                iSampleSC = iSep * obj->nChannels + iChannel;
                                iSampleAC = iActiveSource * obj->nChannels + iChannel;

                                if (masks->array[iSampleSC] == 1) {

                                    Areal = steers->array[iSep][iSampleBC * 2 + 0];
                                    Aimag = steers->array[iSep][iSampleBC * 2 + 1];

                                    Wreal = Areal / gain2;
                                    Wimag = -1.0f * Aimag / gain2;

                                    obj->Wn[nActiveSources-1]->real[iSampleAC] = Wreal;
                                    obj->Wn[nActiveSources-1]->imag[iSampleAC] = Wimag;

                                }

                            }
                            
                        }

                        iActiveSource++;

                    }

                }

                // 
                // Compute Y[k] = Wn[k]X[k]
                //

                cmatrix_mul(obj->Y[nActiveSources-1], 
                            obj->Wn[nActiveSources-1], 
                            obj->X);
                   
                //
                // Compute Y^H[k]
                //

                cmatrix_hermitian(obj->YH[nActiveSources-1], 
                                  obj->Y[nActiveSources-1]);

                //
                // Compute Ryy[k] = Y[k] Y[k]^H
                //

                cmatrix_mul(obj->Ryy[nActiveSources-1],
                            obj->Y[nActiveSources-1],
                            obj->YH[nActiveSources-1]);

                //
                // Compute E[k] = Ryy[k] - diag{Ryy[k]}
                //

                cmatrix_copy_cmatrix(obj->E[nActiveSources-1],
                                     obj->Ryy[nActiveSources-1]);

                for (iActiveSource = 0; iActiveSource < nActiveSources; iActiveSource++) {

                    obj->E[nActiveSources-1]->real[iActiveSource * nActiveSources + iActiveSource] = 0.0f;
                    obj->E[nActiveSources-1]->imag[iActiveSource * nActiveSources + iActiveSource] = 0.0f;

                }

                //
                // Compute A[k] and A^H[k]
                //

                iActiveSource = 0;

                cmatrix_zero(obj->A[nActiveSources-1]);
                cmatrix_zero(obj->AH[nActiveSources-1]);

                for (iSep = 0; iSep < obj->nSeps; iSep++) {

                    if (tracks->ids[iSep] != 0) {

                        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                            iSampleBC = iBin * obj->nChannels + iChannel;
                            iSampleSC = iSep * obj->nChannels + iChannel;                           
                            iSampleCA = iChannel * nActiveSources + iActiveSource;
                            iSampleAC = iActiveSource * obj->nChannels + iChannel;

                            if (masks->array[iSampleSC] == 1) {

                                Areal = steers->array[iSep][iSampleBC * 2 + 0];
                                Aimag = steers->array[iSep][iSampleBC * 2 + 1];

                                obj->A[nActiveSources-1]->real[iSampleCA] = Areal;
                                obj->A[nActiveSources-1]->imag[iSampleCA] = Aimag;

                                obj->AH[nActiveSources-1]->real[iSampleAC] = Areal;
                                obj->AH[nActiveSources-1]->imag[iSampleAC] = -1.0f * Aimag;

                            }

                        }

                        iActiveSource++;

                    }

                }

                //
                // Compute dJ1[k] = 4{E[k]Wn[k]X[k]}X^H[k] = 4{E[k]Y[k]}X^H[k]
                //

                // E[k]Y[k]

                cmatrix_mul(obj->dJ1_EY[nActiveSources-1],
                            obj->E[nActiveSources-1],
                            obj->Y[nActiveSources-1]);

                // 4E[k]Y[k]

                cmatrix_scale(obj->dJ1_4EY[nActiveSources-1],
                              obj->dJ1_EY[nActiveSources-1],
                              4.0f);

                // 4E[k]Y[k]X^H[k]

                cmatrix_mul(obj->dJ1_4EYXH[nActiveSources-1],
                            obj->dJ1_4EY[nActiveSources-1],
                            obj->XH);

                // Copy

                cmatrix_copy_cmatrix(obj->dJ1[nActiveSources-1],
                                     obj->dJ1_4EYXH[nActiveSources-1]);

                //
                // Compute dJ2[k] = 2{W[k]A[k]-I}A^H[k]
                //                

                // W[k]A[k]

                cmatrix_mul(obj->dJ2_WA[nActiveSources-1],
                            obj->Wn[nActiveSources-1],
                            obj->A[nActiveSources-1]);                

                // W[k]A[k] - I

                cmatrix_copy_cmatrix(obj->dJ2_WAmI[nActiveSources-1],
                                     obj->dJ2_WA[nActiveSources-1]);

                for (iActiveSource = 0; iActiveSource < nActiveSources; iActiveSource++)                 {
                    obj->dJ2_WAmI[nActiveSources-1]->real[iActiveSource * nActiveSources + iActiveSource] -= 1.0f;
                }

                // 2{W[k]A[k]-I}

                cmatrix_scale(obj->dJ2_2WAmI[nActiveSources-1],
                              obj->dJ2_WAmI[nActiveSources-1],
                              2.0f);

                // 2{W[k]A[k]-I}A^H[k]

                cmatrix_mul(obj->dJ2_2WAmIAH[nActiveSources-1],
                            obj->dJ2_2WAmI[nActiveSources-1],
                            obj->AH[nActiveSources-1]);

                // Copy

                cmatrix_copy_cmatrix(obj->dJ2[nActiveSources-1],
                                     obj->dJ2_2WAmIAH[nActiveSources-1]);


                //if (iBin == 10) {
                //    cmatrix_printf(obj->AH[nActiveSources-1]);
                //}

                //
                // Compute ||Rxx||^2 = ||X[k]X^H[k]||^2 = (||X[k]||^2)^2
                //

                X2 = 0.0f;

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    Xreal = obj->X->real[iChannel];
                    Ximag = obj->X->imag[iChannel];

                    X2 += Xreal * Xreal + Ximag * Ximag;

                }

                Rxx2 = X2 * X2;

                //
                // Compute alpha = 1 / ||Rxx||^2
                //

                alpha = 1.0f / (Rxx2 + obj->epsilon);

                //
                // Compute W_n+1[k] = (1 - lambda * mu) * W_n[k] - mu * {alpha * dJ1 + dJ2}
                //

                // alpha * dJ1

                cmatrix_scale(obj->alpha_dJ1[nActiveSources-1],
                              obj->dJ1[nActiveSources-1],
                              alpha);

                // alpha * dJ1 + dJ2

                cmatrix_add(obj->alpha_dJ1_p_dJ2[nActiveSources-1],
                            obj->alpha_dJ1[nActiveSources-1],
                            obj->dJ2[nActiveSources-1]);

                // mu * (alpha * dJ1 + dJ2)

                cmatrix_scale(obj->mu_alpha_dJ1_p_dJ2[nActiveSources-1],
                              obj->alpha_dJ1_p_dJ2[nActiveSources-1],
                              1.0f * obj->mu);

                // (1 - lambda * mu) * Wn

                cmatrix_scale(obj->one_m_lambda_mu_Wn[nActiveSources-1],
                              obj->Wn[nActiveSources-1],
                              (1.0f - obj->lambda * obj->mu));

                // (1 - lambda * mu) * Wn[k] - mu * {alpha * dJ1[k] + dJ2[k]}

                cmatrix_sub(obj->one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2[nActiveSources-1],
                            obj->one_m_lambda_mu_Wn[nActiveSources-1],
                            obj->mu_alpha_dJ1_p_dJ2[nActiveSources-1]);

                // Copy

                cmatrix_copy_cmatrix(obj->Wnp1[nActiveSources-1],
                                     obj->one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2[nActiveSources-1]);

                //
                // Copy to demixing
                //

                iActiveSource = 0;

                for (iSep = 0; iSep < obj->nSeps; iSep++) {

                    if (tracks->ids[iSep] != 0) {

                        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                            iSampleBC = iBin * obj->nChannels + iChannel;
                            iSampleAC = iActiveSource * obj->nChannels + iChannel;

                            Wreal = obj->Wnp1[nActiveSources-1]->real[iSampleAC];
                            Wimag = obj->Wnp1[nActiveSources-1]->imag[iSampleAC];

                            demixings->array[iSep][iSampleBC * 2 + 0] = Wreal;
                            demixings->array[iSep][iSampleBC * 2 + 1] = Wimag;

                        }

                        iActiveSource++;

                    }               

                }

            }

        }

                //        count++;

                //if (count == 1) {
                //    exit(EXIT_SUCCESS);
                //}

    }
    
    steer2demixing_mvdr_obj * steer2demixing_mvdr_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float alpha, const float sigma, const unsigned int deltaK) {

        // Not implemented yet

    }

    void steer2demixing_mvdr_destroy(steer2demixing_mvdr_obj * obj) {

        // Not implemented yet

    }

    void steer2demixing_mvdr_process(steer2demixing_mvdr_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, demixings_obj * demixings) {

        // Not implemented yet

    }

