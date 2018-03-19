   
   /**
    * \file     pitch.c
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
    
    #include <signal/pitch.h>

    pitches_obj * pitches_construct_zero(const unsigned int nSignals) {

        pitches_obj * obj;

        obj = (pitches_obj *) malloc(sizeof(pitches_obj));

        obj->nSignals = nSignals;
        obj->array = (float *) malloc(sizeof(float) * nSignals);
        memset(obj->array, 0x00, sizeof(float) * nSignals);

        return obj;

    }

    void pitches_destroy(pitches_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pitches_copy(pitches_obj * dest, const pitches_obj * src) {

        memcpy(dest->array, src->array, sizeof(float) * src->nSignals);

    }

    void pitches_zero(pitches_obj * obj) {

        memset(obj->array, 0x00, sizeof(float) * obj->nSignals);

    }

    void pitches_printf(const pitches_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %1.5f\n",iSignal,obj->array[iSignal]);

        }

    }
