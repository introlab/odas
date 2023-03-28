
   /**
    * \file     mixture2mixture.c
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

    #include <system/mixture2mixture.h>

    mixture2mixture_obj * mixture2mixture_construct(const gaussians_1d_obj * active_gmm, const gaussians_1d_obj * inactive_gmm, const float diffuse_cst, const float Pfalse, const float Pnew, const float Ptrack, const float epsilon) {

        mixture2mixture_obj * obj;

        obj = (mixture2mixture_obj *) malloc(sizeof(mixture2mixture_obj));

        obj->active = gaussians_1d_construct_gaussians(active_gmm);
        obj->inactive = gaussians_1d_construct_gaussians(inactive_gmm);
        obj->diffuse = diffuse_cst;

        obj->Pfalse = Pfalse;
        obj->Pnew = Pnew;
        obj->Ptrack = Ptrack;
        obj->epsilon = epsilon;

        return obj;

    }

    void mixture2mixture_destroy(mixture2mixture_obj * obj) {

        gaussians_1d_destroy(obj->active);
        gaussians_1d_destroy(obj->inactive);

        free((void *) obj);

    }

    void mixture2mixture_process(mixture2mixture_obj * obj, mixture_obj * mixture, const pots_obj * pots, const coherences_obj * coherences, postprobs_obj * postprobs) {

        unsigned int iPot;
        unsigned int iTrack;
        unsigned int iTrackNewFalse;
        unsigned int iCombination;

        signed int t;
        float total;
        unsigned char match;

        // Compute likelihood

        // p(E^s_l|A), p(E^s_l|I) & p(z^s_l|D)

        for (iPot = 0; iPot < mixture->nPots; iPot++) {

            mixture->p_Ez_AICD[0 * pots->nPots + iPot] = gaussians_1d_eval(obj->active, pots->array[iPot * 4 + 3]);
            mixture->p_Ez_AICD[1 * pots->nPots + iPot] = gaussians_1d_eval(obj->inactive, pots->array[iPot * 4 + 3]);
            mixture->p_Ez_AICD[2 * pots->nPots + iPot] = obj->diffuse;

        }

        // p(z^s_l|C,t)

        for (iTrack = 0; iTrack < mixture->nTracks; iTrack++) {

            for (iPot = 0; iPot < mixture->nPots; iPot++) {

                mixture->p_Ez_AICD[(3 + iTrack) * pots->nPots + iPot] = coherences->array[iTrack * mixture->nPots + iPot];

            }

        }

        // p(E^s_l,z^s_l|phis_c)

        for (iPot = 0; iPot < mixture->nPots; iPot++) {

            for (iTrackNewFalse = 0; iTrackNewFalse < mixture->nTracksNewFalse; iTrackNewFalse++) {

                t = (((signed int) iTrackNewFalse) - 2);

                if (t == -2) {

                    mixture->p_Eszs_phics[iTrackNewFalse * mixture->nPots + iPot] = mixture->p_Ez_AICD[1 * pots->nPots + iPot] * mixture->p_Ez_AICD[2 * pots->nPots + iPot];

                }
                else if (t == -1) {

                    mixture->p_Eszs_phics[iTrackNewFalse * mixture->nPots + iPot] = mixture->p_Ez_AICD[0 * pots->nPots + iPot] * mixture->p_Ez_AICD[2 * pots->nPots + iPot];

                }
                else {

                    mixture->p_Eszs_phics[iTrackNewFalse * mixture->nPots + iPot] = mixture->p_Ez_AICD[0 * pots->nPots + iPot] * mixture->p_Ez_AICD[(t + 3) * pots->nPots + iPot];

                }

            }

        }

        // Prior probabilities

        for (iPot = 0; iPot < mixture->nPots; iPot++) {

            for (iTrackNewFalse = 0; iTrackNewFalse < mixture->nTracksNewFalse; iTrackNewFalse++) {

                t = (((signed int) iTrackNewFalse) - 2);

                if (t == -2) {

                    mixture->p_phics[iTrackNewFalse * mixture->nPots + iPot] = obj->Pfalse;

                }
                else if (t == -1) {

                    mixture->p_phics[iTrackNewFalse * mixture->nPots + iPot] = obj->Pnew;

                }
                else {

                    mixture->p_phics[iTrackNewFalse * mixture->nPots + iPot] = obj->Ptrack;

                }                    

            }

        }

        // Posterior probabilities

        total = obj->epsilon;

        for (iCombination = 0; iCombination < mixture->nCombinations; iCombination++) {

            mixture->p_Ez_phic[iCombination] = 1.0f;
            mixture->p_phic[iCombination] = 1.0f;

            for (iPot = 0; iPot < mixture->nPots; iPot++) {

                t = mixture->assignations->array[iCombination * mixture->nPots + iPot];
                iTrackNewFalse = (unsigned int) (t + 2);

                mixture->p_Ez_phic[iCombination] *= mixture->p_Eszs_phics[iTrackNewFalse * mixture->nPots + iPot];
                mixture->p_phic[iCombination] *= mixture->p_phics[iTrackNewFalse * mixture->nPots + iPot];

            }

            mixture->p_phic_Ez[iCombination] = mixture->p_Ez_phic[iCombination] * mixture->p_phic[iCombination];

            total += mixture->p_phic_Ez[iCombination];

        }

        for (iCombination = 0; iCombination < mixture->nCombinations; iCombination++) {

            mixture->p_phic_Ez[iCombination] /= total;

        }

        // Tracking - Potential probabilities

        for (iTrack = 0; iTrack < mixture->nTracks; iTrack++) {

            t = ((signed int) iTrack);

            for (iPot = 0; iPot < mixture->nPots; iPot++) {

                postprobs->arrayTrack[iTrack * mixture->nPots + iPot] = 0.0f;

                for (iCombination = 0; iCombination < mixture->nCombinations; iCombination++) {

                    if (mixture->assignations->array[iCombination * mixture->nPots + iPot] == t) {

                        postprobs->arrayTrack[iTrack * mixture->nPots + iPot] += mixture->p_phic_Ez[iCombination];

                    }

                }

            }    

        }

        // New probabilities

        postprobs->arrayNew[0] = 0.0f;

        for (iPot = 0; iPot < mixture->nPots; iPot++) {

            postprobs->arrayNew[iPot] = 0.0f;

            for (iCombination = 0; iCombination < mixture->nCombinations; iCombination++) {

                if (mixture->assignations->array[iCombination * mixture->nPots + iPot] == -1) {

                    postprobs->arrayNew[iPot] += mixture->p_phic_Ez[iCombination];

                }

            }

        }                 

        // Tracking probabilities

        for (iTrack = 0; iTrack < mixture->nTracks; iTrack++) {

            t = ((signed int) iTrack);
            postprobs->arrayTrackTotal[iTrack] = 0.0f;

            for (iCombination = 0; iCombination < mixture->nCombinations; iCombination++) {

                match = 0;

                for (iPot = 0; iPot < mixture->nPots; iPot++) {

                    if (mixture->assignations->array[iCombination * mixture->nPots + iPot] == t) {

                        match = 1;
                        break;

                    }

                }

                if (match == 1) {

                    postprobs->arrayTrackTotal[iTrack] += mixture->p_phic_Ez[iCombination];

                }

            }              

        }

    }
