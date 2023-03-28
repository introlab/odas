
   /**
    * \file     delay.c
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

    #include <init/delay.h>

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize, const unsigned int interpRate) {

        tdoas_obj * obj;

        unsigned int nPairs;
        
        unsigned int iChannel1;
        unsigned int iChannel2;
        unsigned int iPair;
        unsigned int iPoint;

        float diff, dist, tau;
        unsigned int tdoa;

        nPairs = mics->nChannels * (mics->nChannels -1) / 2;

        obj = tdoas_construct_zero(points->nPoints,nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {

            obj->min[iPair] = frameSize * interpRate - 1;
            obj->max[iPair] = 0;

        }

        for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

            iPair = 0;

            for (iChannel1 = 0; iChannel1 < mics->nChannels; iChannel1++) {

                for (iChannel2 = (iChannel1+1); iChannel2 < mics->nChannels; iChannel2++) {

                    dist = 0.0f;
                    dist += (mics->mu[iChannel1*3+0] - mics->mu[iChannel2*3+0]) * points->array[iPoint*3+0];
                    dist += (mics->mu[iChannel1*3+1] - mics->mu[iChannel2*3+1]) * points->array[iPoint*3+1];                    
                    dist += (mics->mu[iChannel1*3+2] - mics->mu[iChannel2*3+2]) * points->array[iPoint*3+2];                    

                    tau = -1.0f * (((float) fS * interpRate) / soundspeed->mu) * dist;

                    tdoa = (unsigned int) (roundf(tau)+(float) (interpRate * frameSize/2));
                    obj->array[iPoint*nPairs+iPair] = tdoa;

                    if (tdoa < obj->min[iPair]) {
                        obj->min[iPair] = tdoa;
                    }
                    if (tdoa > obj->max[iPair]) {
                        obj->max[iPair] = tdoa;
                    }

                    iPair++;

                }

            }

        }

        return obj;

    }

    taus_obj * delay_taus(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize, const unsigned int interpRate) {

        taus_obj * obj;

        unsigned int nPairs;

        unsigned int iChannel1;
        unsigned int iChannel2;
        unsigned int iPair;
        unsigned int iPoint;

        float mu_t;
        float sigma2_t;
        float mu_d;
        float sigma2_d;
        float mu_tau;
        float sigma2_tau;

        float mu_ij_x, mu_ij_y, mu_ij_z;
        float sigma_ij_xx, sigma_ij_xy, sigma_ij_xz;
        float sigma_ij_yx, sigma_ij_yy, sigma_ij_yz;
        float sigma_ij_zx, sigma_ij_zy, sigma_ij_zz;

        nPairs = mics->nChannels * (mics->nChannels -1) / 2;

        obj = taus_construct_zero(points->nPoints, nPairs);

        mu_t = -1.0f * ((float) fS * interpRate) / soundspeed->mu;
        sigma2_t = ((float) fS * interpRate) * ((float) fS * interpRate) * soundspeed->sigma2 / (soundspeed->mu * soundspeed->mu * soundspeed->mu * soundspeed->mu);

        iPair = 0;

        for (iChannel1 = 0; iChannel1 < mics->nChannels; iChannel1++) {

            for (iChannel2 = (iChannel1+1); iChannel2 < mics->nChannels; iChannel2++) {

                mu_ij_x = mics->mu[iChannel1*3+0] - mics->mu[iChannel2*3+0];
                mu_ij_y = mics->mu[iChannel1*3+1] - mics->mu[iChannel2*3+1];
                mu_ij_z = mics->mu[iChannel1*3+2] - mics->mu[iChannel2*3+2];

                sigma_ij_xx = mics->sigma2[iChannel1*9+0] + mics->sigma2[iChannel2*9+0];
                sigma_ij_xy = mics->sigma2[iChannel1*9+1] + mics->sigma2[iChannel2*9+1];
                sigma_ij_xz = mics->sigma2[iChannel1*9+2] + mics->sigma2[iChannel2*9+2];
                sigma_ij_yx = mics->sigma2[iChannel1*9+3] + mics->sigma2[iChannel2*9+3];
                sigma_ij_yy = mics->sigma2[iChannel1*9+4] + mics->sigma2[iChannel2*9+4];
                sigma_ij_yz = mics->sigma2[iChannel1*9+5] + mics->sigma2[iChannel2*9+5];
                sigma_ij_zx = mics->sigma2[iChannel1*9+6] + mics->sigma2[iChannel2*9+6];
                sigma_ij_zy = mics->sigma2[iChannel1*9+7] + mics->sigma2[iChannel2*9+7];
                sigma_ij_zz = mics->sigma2[iChannel1*9+8] + mics->sigma2[iChannel2*9+8];

                for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

                    mu_d = mu_ij_x * points->array[iPoint*3+0] + 
                           mu_ij_y * points->array[iPoint*3+1] + 
                           mu_ij_z * points->array[iPoint*3+2];

                    sigma2_d = points->array[iPoint*3+0] * sigma_ij_xx * points->array[iPoint*3+0] + 
                               points->array[iPoint*3+0] * sigma_ij_xy * points->array[iPoint*3+1] + 
                               points->array[iPoint*3+0] * sigma_ij_xz * points->array[iPoint*3+2] + 
                               points->array[iPoint*3+1] * sigma_ij_yx * points->array[iPoint*3+0] + 
                               points->array[iPoint*3+1] * sigma_ij_yy * points->array[iPoint*3+1] + 
                               points->array[iPoint*3+1] * sigma_ij_yz * points->array[iPoint*3+2] + 
                               points->array[iPoint*3+2] * sigma_ij_zx * points->array[iPoint*3+0] + 
                               points->array[iPoint*3+2] * sigma_ij_zy * points->array[iPoint*3+1] + 
                               points->array[iPoint*3+2] * sigma_ij_zz * points->array[iPoint*3+2];

                    mu_tau = mu_t * mu_d;
                    sigma2_tau = mu_t*mu_t*sigma2_d + mu_d*mu_d*sigma2_t;

                    obj->mu[iPoint*nPairs+iPair] = mu_tau + (float) (interpRate*frameSize/2);
                    obj->sigma2[iPoint*nPairs+iPair] = sigma2_tau;

                }

                iPair++;

            }

        }

        return obj;

    }
