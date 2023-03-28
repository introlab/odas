
   /**
    * \file     linking.c
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

    #include <init/linking.h>

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const deltas_obj * deltasCoarse, const deltas_obj * deltasFine, const spatialmasks_obj * spatialmasksCoarse, const spatialmasks_obj * spatialmasksFine, const unsigned int nMatches) {

        maps_obj * obj;
        float * scores;
        
        unsigned int lambdaCoarseLeft;
        unsigned int lambdaCoarseRight;
        unsigned int lambdaFineLeft;
        unsigned int lambdaFineRight;

        float score;

        unsigned int iFine;
        unsigned int iCoarse;
        unsigned int iPair;
        unsigned int iMatch;

        unsigned int nFines;
        unsigned int nCoarses;
        unsigned int nPairs;
        
        char isActive;

        float maxValue;
        unsigned int maxIndex;

        if (tdoasCoarse != NULL) {

            nFines = tdoasFine->nPoints;
            nCoarses = tdoasCoarse->nPoints;
            nPairs = tdoasFine->nPairs;

            obj = maps_construct_zero(nCoarses, nFines);
            scores = (float *) malloc(sizeof(float) * nCoarses);

            for (iFine = 0; iFine < nFines; iFine++) {

                isActive = 0x00;

                for (iPair = 0; iPair < nPairs; iPair++) {

                    if (spatialmasksFine->array[iFine * nPairs + iPair] == 0x01) {

                        isActive = 0x01;
                        break;

                    }

                }

                if (isActive == 0x01) {

                    for (iCoarse = 0; iCoarse < nCoarses; iCoarse++) {

                        scores[iCoarse] = 0.0f;

                        for (iPair = 0; iPair < nPairs; iPair++) {

                            if ((spatialmasksCoarse->array[iCoarse * nPairs + iPair] == 0x01) && (spatialmasksFine->array[iFine * nPairs + iPair] == 0x01)) {

                                lambdaCoarseLeft = tdoasCoarse->array[iCoarse * nPairs + iPair] - deltasCoarse->array[iPair];
                                lambdaCoarseRight = tdoasCoarse->array[iCoarse * nPairs + iPair] + deltasCoarse->array[iPair];
                                lambdaFineLeft = tdoasFine->array[iFine * nPairs + iPair] - deltasFine->array[iPair];
                                lambdaFineRight = tdoasFine->array[iFine * nPairs + iPair] + deltasFine->array[iPair];

                                scores[iCoarse] += linking_overlap(lambdaCoarseLeft,lambdaCoarseRight,lambdaFineLeft,lambdaFineRight);

                            }

                        }

                    }

                    for (iMatch = 0; iMatch < nMatches; iMatch++) {

                        maxValue = 0.0f;
                        maxIndex = 0;

                        for (iCoarse = 0; iCoarse < nCoarses; iCoarse++) {

                            if (scores[iCoarse] > maxValue) {

                                maxValue = scores[iCoarse];
                                maxIndex = iCoarse;

                            }

                        }

                        obj->array[iFine * obj->nCoarses + maxIndex] = 0x01;
                        scores[maxIndex] = 0.0f;

                    }

                }

            }

            free((void *) scores);

        }
        else {

            nFines = tdoasFine->nPoints;
            nPairs = tdoasFine->nPairs;

            obj = maps_construct_zero(1, nFines);

            for (iFine = 0; iFine < nFines; iFine++) {

                for (iPair = 0; iPair < nPairs; iPair++) {

                    if (spatialmasksFine->array[iFine * nPairs + iPair] == 0x01) {

                        obj->array[iFine] = 0x01;
                        break;

                    }

                }

            }

        }

        return obj;

    }

    indexes_obj * linking_indexes(const maps_obj * maps) {

        indexes_obj * obj;

        unsigned int iFine;
        unsigned int iCoarse;
        unsigned int nFines;
        unsigned int nFinesMax;

        nFinesMax = 0;

        for (iCoarse = 0; iCoarse < maps->nCoarses; iCoarse++) {

            nFines = 0;

            for (iFine = 0; iFine < maps->nFines; iFine++) {

                if (maps->array[iFine * maps->nCoarses + iCoarse] == 0x01) {

                    nFines++;

                }

            }

            if (nFines > nFinesMax) {
                nFinesMax = nFines;
            }

        }

        obj = indexes_construct_zero(maps->nCoarses,nFinesMax);

        for (iCoarse = 0; iCoarse < maps->nCoarses; iCoarse++) {

            nFines = 0;

            for (iFine = 0; iFine < maps->nFines; iFine++) {

                if (maps->array[iFine * maps->nCoarses + iCoarse] == 0x01) {

                    obj->array[iCoarse * nFinesMax + nFines] = iFine;
                    nFines++;

                }

            }

            obj->count[iCoarse] = nFines;

        }        

        return obj;

    }

    float linking_overlap(const float lambdaCoarseLeft, const float lambdaCoarseRight, const float lambdaFineLeft, const float lambdaFineRight) {

        float overlap;
        float lambdaMaxLeft;
        float lambdaMinRight;

        if ((lambdaCoarseRight >= lambdaFineLeft) && (lambdaCoarseLeft <= lambdaFineRight)) {

            if (lambdaCoarseLeft > lambdaFineLeft) {

                lambdaMaxLeft = lambdaCoarseLeft;

            }
            else {

                lambdaMaxLeft = lambdaFineLeft;

            }

            if (lambdaCoarseRight < lambdaFineRight) {

                lambdaMinRight = lambdaCoarseRight;

            }
            else {

                lambdaMinRight = lambdaFineRight;

            }
            
            overlap = lambdaMinRight - lambdaMaxLeft + 1.0f;

        }
        else {
            
            overlap = 0.0f;

        }

        return overlap;

    }
