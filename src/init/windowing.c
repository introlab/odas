
   /**
    * \file     windowing.c
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

    #include <init/windowing.h>

    window_obj * windowing_hann(const unsigned int frameSize) {

        window_obj * obj;
        unsigned int iSample;

        obj = window_construct_zero(frameSize);

        if ( frameSize == 1 ) {

        	obj->array[0] = 1.0f;

        }
        else {

            for ( iSample = 0; iSample < frameSize; iSample++ ) {
                
                obj->array[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( frameSize - 1 ) ) ) );
                                
            }


        }

        return obj;

    }

    window_obj * windowing_roothann(const unsigned int frameSize) {

        window_obj * obj;
        unsigned int iSample;

        obj = window_construct_zero(frameSize);

        if ( frameSize == 1 ) {

            obj->array[0] = 1.0f;

        }
        else {

            for ( iSample = 0; iSample < frameSize; iSample++ ) {

                obj->array[iSample] = sqrtf( 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( frameSize - 1 ) ) ) ) );

            }

        }

        return obj;

    }
