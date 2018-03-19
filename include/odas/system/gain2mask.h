#ifndef __ODAS_SYSTEM_GAIN2MASK
#define __ODAS_SYSTEM_GAIN2MASK

   /**
    * \file     gain2mask.h
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

    #include <signal/gain.h>
    #include <signal/mask.h>

    #include <stdlib.h>
    #include <string.h>

    typedef struct gain2mask_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float gainMin;

    } gain2mask_obj;

    gain2mask_obj * gain2mask_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float gainMin);

    void gain2mask_destroy(gain2mask_obj * obj);

    void gain2mask_process(gain2mask_obj * obj, const gains_obj * gains, masks_obj * masks);

#endif
