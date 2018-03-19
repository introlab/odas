
   /**
    * \file     gain.c
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

    gains_obj * gains_construct_zero(const unsigned int nSeps, const unsigned int nChannels) {

        gains_obj * obj;

        obj = (gains_obj *) malloc(sizeof(gains_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        
        obj->array = (float *) malloc(sizeof(float) * nSeps * nChannels);
        memset(obj->array, 0x00, sizeof(float) * nSeps * nChannels);

        return obj;

    }

    void gains_destroy(gains_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void gains_printf(const gains_obj * obj) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("(%02u): ",iSep);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%+1.3f ",obj->array[iSep * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }
