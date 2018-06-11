
   /**
    * \file     pitch2category.c
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
