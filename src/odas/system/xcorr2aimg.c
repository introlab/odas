
   /**
    * \file     xcorr2aimg.c
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
