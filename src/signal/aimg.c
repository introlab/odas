
   /**
    * \file     aimg.c
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
    
    #include <signal/aimg.h>

    aimg_obj * aimg_construct_zero(const unsigned int aimgSize) {

        aimg_obj * obj;

        obj = (aimg_obj *) malloc(sizeof(aimg_obj));

        obj->aimgSize = aimgSize;
        obj->array = (float *) malloc(sizeof(float) * aimgSize);
        memset(obj->array, 0x00, aimgSize * sizeof(float));       

        return obj;

    }

    void aimg_destroy(aimg_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void aimg_printf(const aimg_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSample = 0; iSample < obj->aimgSize; iSample++) {

            printf("%+1.5f ",obj->array[iSample]);

            if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->aimgSize)) {
                printf("\n");
            }

        }

        printf("\n");

    }
