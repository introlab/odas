
   /**
    * \file     xcorr2aimg.c
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
    
    #include <system/xcorr2aimg.h>

    xcorr2aimg_obj * xcorr2aimg_construct_zero(const unsigned int aimgSize) {

        xcorr2aimg_obj * obj;

        obj = (xcorr2aimg_obj *) malloc(sizeof(xcorr2aimg_obj));

        obj->aimgSize = aimgSize;

        return obj;

    }

    void xcorr2aimg_destroy(xcorr2aimg_obj * obj) {

        free((void *) obj);

    }

    void xcorr2aimg_process(xcorr2aimg_obj * obj, const tdoas_obj * tdoas, const indexes_obj * indexes, const spatialindexes_obj * spatialindexes, const unsigned int iCoarse, const xcorrs_obj * xcorrs, aimg_obj * aimg) {

        unsigned int iSpatialIndex;
        unsigned int iPair;
        unsigned int iFine;
        unsigned int iPoint;
        unsigned int tau;

        memset(aimg->array, 0x00, sizeof(float) * aimg->aimgSize);

        for (iFine = 0; iFine < indexes->count[iCoarse]; iFine++) {

            iPoint = indexes->array[iCoarse * indexes->nFines + iFine];

            for (iSpatialIndex = 0; iSpatialIndex < spatialindexes->count[iPoint]; iSpatialIndex++) {

                iPair = spatialindexes->array[iPoint * spatialindexes->nPairs + iSpatialIndex];

                tau = tdoas->array[iPoint * tdoas->nPairs + iPair];

                aimg->array[iPoint] += xcorrs->array[iPair][tau];

            }

            aimg->array[iPoint] /= ((float) spatialindexes->count[iPoint]);     

        }

        

    }
