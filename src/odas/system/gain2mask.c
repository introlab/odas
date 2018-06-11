
   /**
    * \file     gain2mask.c
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
    
    #include <system/gain2mask.h>

    gain2mask_obj * gain2mask_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float gainMin) {

        gain2mask_obj * obj;

        obj = (gain2mask_obj *) malloc(sizeof(gain2mask_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->gainMin = gainMin;

        return obj;

    }

    void gain2mask_destroy(gain2mask_obj * obj) {

        free((void *) obj);

    }

    void gain2mask_process(gain2mask_obj * obj, const gains_obj * gains, masks_obj * masks) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                if (gains->array[iSep * obj->nChannels + iChannel] >= obj->gainMin) {
                    masks->array[iSep * obj->nChannels + iChannel] = 0x01;
                }
                else {
                    masks->array[iSep * obj->nChannels + iChannel] = 0x00;
                }

            }

        }

    }
