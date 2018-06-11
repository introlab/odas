   
   /**
    * \file     spatialgain.c
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
    
    #include <signal/spatialgain.h>

    spatialgains_obj * spatialgains_construct_zero(const unsigned int nChannels, const unsigned int nPoints) {

        spatialgains_obj * obj;

        obj = (spatialgains_obj *) malloc(sizeof(spatialgains_obj));

        obj->nChannels = nChannels;
        obj->nPoints = nPoints;

        obj->array = (float *) malloc(sizeof(float) * nChannels * nPoints);
        memset(obj->array, 0x00, sizeof(float) * nChannels * nPoints);

        return obj;

    }

    spatialgains_obj * spatialgains_clone(const spatialgains_obj * obj) {

        spatialgains_obj * clone;

        clone = (spatialgains_obj *) malloc(sizeof(spatialgains_obj));

        clone->nChannels = obj->nChannels;
        clone->nPoints = obj->nPoints;

        clone->array = (float *) malloc(sizeof(float) * obj->nChannels * obj->nPoints);
        memcpy(clone->array, obj->array, sizeof(float) * obj->nChannels * obj->nPoints);

        return clone;

    }

    void spatialgains_destroy(spatialgains_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void spatialgains_printf(const spatialgains_obj * obj) {

        unsigned int iPoint;
        unsigned int iChannel;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%1.2f ",obj->array[iPoint * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }
