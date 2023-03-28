
   /**
    * \file     pitch2category.c
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
    
    #include <system/pitch2category.h>

    pitch2category_obj * pitch2category_construct_zero(const unsigned int nSeps, const float tauMin, const float tauMax, const float deltaTauMax, const float alpha, const float gamma, const float phiMin, const float r0) {

        pitch2category_obj * obj;

        obj = (pitch2category_obj *) malloc(sizeof(pitch2category_obj));

        obj->nSeps = nSeps;

        obj->tauMin = tauMin;
        obj->tauMax = tauMax;
        obj->deltaTauMax = deltaTauMax;
        obj->alpha = alpha;
        obj->gamma = gamma;
        obj->phiMin = phiMin;
        obj->r0 = r0;

        obj->tausNow = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->tausNow, 0x00, sizeof(float) * nSeps);

        obj->tausPrev = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->tausPrev, 0x00, sizeof(float) * nSeps);

        obj->deltaTausNow = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->deltaTausNow, 0x00, sizeof(float) * nSeps);

        obj->deltaTausPrev = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->deltaTausPrev, 0x00, sizeof(float) * nSeps);

        obj->phisNow = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->phisNow, 0x00, sizeof(float) * nSeps);

        obj->phisPrev = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->phisPrev, 0x00, sizeof(float) * nSeps);        

        obj->vs = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->vs, 0x00, sizeof(float) * nSeps);

        obj->rs = (float *) malloc(sizeof(float) * nSeps);
        memset(obj->rs, 0x00, sizeof(float) * nSeps);

        obj->categories = (char *) malloc(sizeof(char) * nSeps);
        memset(obj->categories, 0x00, sizeof(char) * nSeps);

        return obj;

    }

    void pitch2category_destroy(pitch2category_obj * obj) {

        free((void *) obj->tausNow);
        free((void *) obj->tausPrev);
        free((void *) obj->deltaTausNow);
        free((void *) obj->deltaTausPrev);
        free((void *) obj->phisNow);
        free((void *) obj->phisPrev);
        free((void *) obj->vs);
        free((void *) obj->rs);
        free((void *) obj->categories);

        free((void *) obj);

    }

    void pitch2category_process(pitch2category_obj * obj, const pitches_obj * pitches, const tracks_obj * tracks, categories_obj * categories) {

        unsigned int iSep;
        float deltaPitch;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                if (obj->categories[iSep] != 0x01) {

                    // tau_i
                    obj->tausNow[iSep] = pitches->array[iSep];

                    // delta_tau_i
                    obj->deltaTausNow[iSep] = obj->tausNow[iSep] - obj->tausPrev[iSep];

                    // phi_i
                    if ((fabs(obj->deltaTausNow[iSep]) < obj->deltaTauMax) && (fabs(obj->deltaTausPrev[iSep]) < obj->deltaTauMax)) {

                        obj->phisNow[iSep] = (1 - obj->alpha) * obj->phisPrev[iSep] + obj->alpha * obj->deltaTausNow[iSep];

                    }
                    else if ((fabs(obj->deltaTausNow[iSep]) < obj->deltaTauMax) && (fabs(obj->deltaTausPrev[iSep]) >= obj->deltaTauMax)) {

                        obj->phisNow[iSep] = obj->deltaTausNow[iSep];

                    }
                    else {

                        obj->phisNow[iSep] = 0.0f;

                    }

                    // v_i
                    if ((obj->tausNow[iSep] >= obj->tauMin) && (obj->tausNow[iSep] <= obj->tauMax) && fabs(obj->phisNow[iSep]) > obj->phiMin) {

                        obj->vs[iSep] = 1.0f;

                    }
                    else {

                        obj->vs[iSep] = 0.0f;

                    }

                    // r_i
                    obj->rs[iSep] = (1.0f - obj->gamma) * obj->rs[iSep] + obj->gamma * obj->vs[iSep];

                    // Classify

                    if (obj->rs[iSep] > obj->r0) {

                        // Speech
                        obj->categories[iSep] = 0x01;

                    }
                    else {

                        // Non speech
                        obj->categories[iSep] = 0x00;

                    }

                    // tau_i-1 = tau_i
                    memcpy(obj->tausPrev, obj->tausNow, sizeof(float) * obj->nSeps);

                    // delta_tau_i-1 = delta_tau_i
                    memcpy(obj->deltaTausPrev, obj->deltaTausNow, sizeof(float) * obj->nSeps);

                    // phi_i-1 = phi_i
                    memcpy(obj->phisPrev, obj->phisNow, sizeof(float) * obj->nSeps);

                }

                categories->array[iSep] = obj->categories[iSep];

            }
            else {

                obj->tausNow[iSep] = 0.0f;
                obj->deltaTausNow[iSep] = 0.0f;
                obj->phisNow[iSep] = 0.0f;
                obj->vs[iSep] = 0.0f;
                obj->rs[iSep] = 0.0f;
                obj->categories[iSep] = 0x00;

            }

        }

    }
