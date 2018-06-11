
   /**
    * \file     beampattern.c
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
    
    #include <signal/beampattern.h>

    beampatterns_obj * beampatterns_construct_zero(const unsigned int nChannels, const unsigned int nThetas) {

        beampatterns_obj * obj;

        obj = (beampatterns_obj *) malloc(sizeof(beampatterns_obj));

        obj->nChannels = nChannels;
        obj->nThetas = nThetas;
        
        obj->minThetas = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->minThetas, 0x00, sizeof(float) * nChannels);

        obj->maxThetas = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->maxThetas, 0x00, sizeof(float) * nChannels);

        obj->deltaThetas = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->deltaThetas, 0x00, sizeof(float) * nChannels);
        
        obj->gains = (float *) malloc(sizeof(float) * nThetas * nChannels);
        memset(obj->gains, 0x00, sizeof(float) * nThetas * nChannels);

        return obj;

    }

    void beampatterns_destroy(beampatterns_obj * obj) {

        free((void *) obj->minThetas);
        free((void *) obj->maxThetas);
        free((void *) obj->deltaThetas);
        free((void *) obj->gains);
        free((void *) obj);

    }

    void beampatterns_printf(const beampatterns_obj * obj) {

        unsigned int iChannel;
        unsigned int iTheta;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            for (iTheta = 0; iTheta < obj->nThetas; iTheta++) {

                printf("(%02u,%04u): %1.3f\n", iChannel, iTheta, obj->gains[obj->nThetas * iChannel + iTheta]);

            }

        }

    }
