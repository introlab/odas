
   /**
    * \file     mic.c
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

    #include <general/mic.h>

    mics_obj * mics_construct_zero(const unsigned int nChannels) {

        mics_obj * obj;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nChannels = nChannels;
        obj->nPairs = nChannels * (nChannels - 1) / 2;
        obj->mu = (float *) malloc(sizeof(float) * nChannels * 3);
        memset(obj->mu, 0x00, sizeof(float) * nChannels * 3);        
        obj->sigma2 = (float *) malloc(sizeof(float) * nChannels * 9);
        memset(obj->sigma2, 0x00, sizeof(float) * nChannels * 9);        
        obj->direction = (float *) malloc(sizeof(float) * nChannels * 3);
        memset(obj->direction, 0x00, sizeof(float) * nChannels * 3);
        obj->thetaAllPass = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->thetaAllPass, 0x00, sizeof(float) * nChannels);
        obj->thetaNoPass = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->thetaNoPass, 0x00, sizeof(float) * nChannels);

        return obj;

    }

    mics_obj * mics_clone(const mics_obj * obj) {

        mics_obj * clone;

        clone = (mics_obj *) malloc(sizeof(mics_obj));

        clone->nChannels = obj->nChannels;
        clone->nPairs = obj->nPairs;
        clone->mu = (float *) malloc(sizeof(float) * obj->nChannels * 3);
        memcpy(clone->mu, obj->mu, sizeof(float) * obj->nChannels * 3);
        clone->sigma2 = (float *) malloc(sizeof(float) * obj->nChannels * 9);
        memcpy(clone->sigma2, obj->sigma2, sizeof(float) * obj->nChannels * 9);
        clone->direction = (float *) malloc(sizeof(float) * obj->nChannels * 3);
        memcpy(clone->direction, obj->direction, sizeof(float) * obj->nChannels * 3);
        clone->thetaAllPass = (float *) malloc(sizeof(float) * obj->nChannels);
        memcpy(clone->thetaAllPass, obj->thetaAllPass, sizeof(float) * obj->nChannels);
        clone->thetaNoPass = (float *) malloc(sizeof(float) * obj->nChannels);
        memcpy(clone->thetaNoPass, obj->thetaNoPass, sizeof(float) * obj->nChannels);

        return clone;

    }

    void mics_destroy(mics_obj * obj) {

        free((void *) obj->mu);
        free((void *) obj->sigma2);
        free((void *) obj->direction);
        free((void *) obj->thetaAllPass);
        free((void *) obj->thetaNoPass);

        free((void *) obj);

    }

    void mics_printf(const mics_obj * obj) {

        unsigned int iChannel;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            
            printf("(%02u): mu = (%+1.3f, %+1.3f, %+1.3f)\n",
                   iChannel,
                   obj->mu[iChannel * 3 + 0],
                   obj->mu[iChannel * 3 + 1],
                   obj->mu[iChannel * 3 + 2]);

            printf("               / %+1.3f %+1.3f %+1.3f \\\n",
                   obj->sigma2[iChannel * 9 + 0],
                   obj->sigma2[iChannel * 9 + 1],
                   obj->sigma2[iChannel * 9 + 2]);

            printf("      Sigma2 = | %+1.3f %+1.3f %+1.3f |\n",
                   obj->sigma2[iChannel * 9 + 3],
                   obj->sigma2[iChannel * 9 + 4],
                   obj->sigma2[iChannel * 9 + 5]);

            printf("               \\ %+1.3f %+1.3f %+1.3f /\n",
                   obj->sigma2[iChannel * 9 + 6],
                   obj->sigma2[iChannel * 9 + 7],
                   obj->sigma2[iChannel * 9 + 8]);    

            printf("      direction = (%+1.3f, %+1.3f, %+1.3f)\n",
                   obj->direction[iChannel * 3 + 0],
                   obj->direction[iChannel * 3 + 1],
                   obj->direction[iChannel * 3 + 2]);            

            printf("      thetaAllPass = %+1.3f\n",
                   obj->thetaAllPass[iChannel]);   

            printf("      thetaNoPass = %+1.3f\n",
                   obj->thetaNoPass[iChannel]);   

        }

    }
