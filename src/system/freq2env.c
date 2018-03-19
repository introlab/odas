
   /**
    * \file     freq2env.c
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
   
    #include <system/freq2env.h>

    freq2env_obj * freq2env_construct_zero(const unsigned int halfFrameSize) {

        freq2env_obj * obj;

        obj = (freq2env_obj *) malloc(sizeof(freq2env_obj));

        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void freq2env_destroy(freq2env_obj * obj) {

        free((void *) obj);

    }

    void freq2env_process(freq2env_obj * obj, const freqs_obj * freqs, envs_obj * envs) {

        unsigned int iSignal;
        unsigned int iBin;

        float Xreal;
        float Ximag;
        float X2;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                Xreal = freqs->array[iSignal][iBin * 2 + 0];
                Ximag = freqs->array[iSignal][iBin * 2 + 1];

                X2 = Xreal * Xreal + Ximag * Ximag;

                envs->array[iSignal][iBin] = X2;

            }

        }

    }
