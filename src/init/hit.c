   
   /**
    * \file     hit.c
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

    #include <init/hit.h>

    areas_obj * hit_areas_zero(const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas) {

        areas_obj * areas;

        unsigned int nPointsDiscrete;
        unsigned int nPointsResolution;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        nPointsDiscrete = tdoas->nPoints;
        nPointsResolution = taus->nPoints;
        nResolutionsPerDiscrete = nPointsResolution / nPointsDiscrete;
        nPairs = taus->nPairs;

        areas = areas_construct_zero(nPointsDiscrete, nResolutionsPerDiscrete, nPairs);

        return areas;

    }

    void hit_areas_pair(areas_obj * areas, const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas, const spatialmasks_obj * spatialmasks, const unsigned int iPair) {

        unsigned int iPointDiscrete;
        unsigned int nPointsDiscrete;
        unsigned int iPointResolution;
        unsigned int nPointsResolution;
        unsigned int iResolutionPerDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        float delta;
        float tdoa;

        float mu;
        float sigma2;
        float expr1;
        float expr2;
        float prob;

        nPointsDiscrete = tdoas->nPoints;
        nPointsResolution = taus->nPoints;
        nResolutionsPerDiscrete = nPointsResolution / nPointsDiscrete;
        nPairs = taus->nPairs;

        delta = (float) deltas->array[iPair];

        for (iPointDiscrete = 0; iPointDiscrete < nPointsDiscrete; iPointDiscrete++) {

            tdoa = (float) tdoas->array[iPointDiscrete * nPairs + iPair];

            for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < nResolutionsPerDiscrete; iResolutionPerDiscrete++) {  

                iPointResolution = iPointDiscrete * nResolutionsPerDiscrete + iResolutionPerDiscrete;

                if (spatialmasks->array[iPointDiscrete * nPairs + iPair] == 0x01) {

                    mu = taus->mu[iPointResolution * nPairs + iPair];
                    sigma2 = taus->sigma2[iPointResolution * nPairs + iPair];

                    expr1 = (tdoa + delta + 0.5f - mu) / (sqrtf(2.0f * sigma2));
                    expr2 = (tdoa - delta - 0.5f - mu) / (sqrtf(2.0f * sigma2));

                    prob = 0.5f * (erff(expr1) - erff(expr2));                    

                    areas->array[iPointResolution * nPairs + iPair] = prob;

                }

            }

        }                

    }

    float hit_areas_min(const areas_obj * areas, const spatialmasks_obj * spatialmasks) {

        unsigned int iPointDiscrete;
        unsigned int nPointsDiscrete;
        unsigned int iResolutionPerDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int iPair;
        unsigned int nPairs;
        unsigned int iPointResolution;

        float prob;
        unsigned int count;
        float minValue;
        float minValuePoint;

        nPointsDiscrete = areas->nPointsDiscrete;
        nResolutionsPerDiscrete = areas->nResolutionsPerDiscrete;
        nPairs = areas->nPairs;

        minValue = +INFINITY;

        for (iPointDiscrete = 0; iPointDiscrete < nPointsDiscrete; iPointDiscrete++) {

            count = 0;

            for (iPair = 0; iPair < nPairs; iPair++) {
                
                if (spatialmasks->array[iPointDiscrete * nPairs + iPair] == 0x01) {

                    count++;

                }
                
            }

            if (count > 0) {

                minValuePoint = +INFINITY;

                for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < nResolutionsPerDiscrete; iResolutionPerDiscrete++) {

                    iPointResolution = iPointDiscrete * nResolutionsPerDiscrete + iResolutionPerDiscrete;

                    prob = 0.0f;

                    for (iPair = 0; iPair < nPairs; iPair++) {

                        if (spatialmasks->array[iPointDiscrete * nPairs + iPair] == 0x01) {

                            prob += areas->array[iPointResolution * nPairs + iPair];

                        }

                    }

                    if (prob < minValuePoint) {
                        minValuePoint = prob;
                    }                

                }

                minValuePoint /= ((float) count);

                if (minValuePoint < minValue) {
                    minValue = minValuePoint;
                }

            }

        }

        return minValue;

    }

    area_obj * hit_area_zero(const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas) {

        area_obj * area;

        unsigned int nPairs;

        nPairs = taus->nPairs;

        area = area_construct_zero(nPairs);

        return area;

    }

    void hit_area_pair(area_obj * area, const areas_obj * areas, const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas, const spatialmasks_obj * spatialmasks, const unsigned int iPair) {

        unsigned int iPointDiscrete;
        unsigned int nPointsDiscrete;
        unsigned int iPointResolution;
        unsigned int nPointsResolution;
        unsigned int iResolutionPerDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;
        unsigned int count;

        nPointsDiscrete = tdoas->nPoints;
        nPointsResolution = taus->nPoints;
        nResolutionsPerDiscrete = nPointsResolution / nPointsDiscrete;
        nPairs = taus->nPairs;

        area->array[iPair] = 0.0f;
        count = 0;

        for (iPointDiscrete = 0; iPointDiscrete < nPointsDiscrete; iPointDiscrete++) {

            for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < nResolutionsPerDiscrete; iResolutionPerDiscrete++) {  

                iPointResolution = iPointDiscrete * nResolutionsPerDiscrete + iResolutionPerDiscrete;                

                if (spatialmasks->array[iPointDiscrete * nPairs + iPair] == 0x01) {

                    area->array[iPair] += areas->array[iPointResolution * nPairs + iPair];
                    count++;

                }

            }

        }    

        if (count > 0) {
            area->array[iPair] /= ((float) count);
        }
        else {
            area->array[iPair] = 1.0f;
        }

    }

    deltas_obj * hit_train(const taus_obj * taus, const tdoas_obj * tdoas, const spatialmasks_obj * spatialmasks, const float probMin) {

        deltas_obj * deltas;
        areas_obj * areas;
        area_obj * area;
        
        unsigned int iPair;
        unsigned int nPairs;
        float minValue;
        unsigned int minIndex;

        nPairs = taus->nPairs;

        deltas = deltas_construct_zero(nPairs); 
        areas = hit_areas_zero(taus, tdoas, deltas); 
        area = hit_area_zero(taus, tdoas, deltas);

        for (iPair = 0; iPair < nPairs; iPair++) {

            hit_areas_pair(areas, taus, tdoas, deltas, spatialmasks, iPair);
            hit_area_pair(area, areas, taus, tdoas, deltas, spatialmasks, iPair);

        }

        while(1) {

            minValue = hit_areas_min(areas, spatialmasks);
            
            if (minValue >= probMin) {
                break;
            }

            minValue = +INFINITY;

            for (iPair = 0; iPair < nPairs; iPair++) {

                if (area->array[iPair] < minValue) {
                    minValue = area->array[iPair];
                    minIndex = iPair;
                }
                
            }

            deltas->array[minIndex]++;

            hit_areas_pair(areas, taus, tdoas, deltas, spatialmasks, minIndex);
            hit_area_pair(area, areas, taus, tdoas, deltas, spatialmasks, minIndex);
            
        }

        areas_destroy(areas);
        area_destroy(area);

        return deltas;

    }

    deltas_obj * hit_constant(const tdoas_obj * tdoas, const unsigned int delta) {

        unsigned int iPair;
        unsigned int nPairs;

        deltas_obj * deltas;

        nPairs = tdoas->nPairs;

        deltas = deltas_construct_zero(nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {

            deltas->array[iPair] = delta;

        }

        return deltas;

    }
