   
   /**
    * \file     pcm.c
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

    #include <utils/pcm.h>
    #include <stdio.h>

    void pcm_SXle2normalized(float * normalized, const char * SXle, const unsigned int nBytes, const unsigned int nSamples) {

        unsigned int iSample;
        int sample32;
        const float factor = 2147483648.0f;

        for (iSample = 0; iSample < nSamples; iSample++) {

            sample32 = 0;
            memcpy(&sample32, &(SXle[iSample*nBytes]), nBytes * sizeof(char));
            sample32 <<= (8*(4-nBytes));

            normalized[iSample] = ((float) sample32) / factor;

        }

    }

    void pcm_normalized2SXle(char * SXle, const float * normalized, const unsigned int nBytes, const unsigned int nSamples) {

        unsigned int iSample;
        int sample32;
        char bytes[4];
        const float factor = 2147483648.0f;

        for (iSample = 0; iSample < nSamples; iSample++) {

            sample32 = (signed int) (roundf(normalized[iSample] * factor));

            sample32 >>= (8*(4-nBytes));
            memcpy(&(SXle[iSample*nBytes]), &sample32, nBytes * sizeof(char));

        }

    }
