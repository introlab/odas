
   /**
    * \file     linking.c
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
