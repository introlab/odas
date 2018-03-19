
   /**
    * \file     coherence.c
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

    #include <signal/coherence.h>

    coherences_obj * coherences_construct_zero(const unsigned int nPots, const unsigned int nTracks) {

        coherences_obj * obj;
        obj = (coherences_obj *) malloc(sizeof(coherences_obj));
        obj->nPots = nPots;
        obj->nTracks = nTracks;
        obj->array = (float *) malloc(sizeof(float) * nTracks * nPots);
        memset(obj->array, 0x00, sizeof(float) * nTracks * nPots);

        return obj;

    }

    void coherences_destroy(coherences_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void coherences_printf(coherences_obj * obj) {

        unsigned int iTrack;
        unsigned int iPot;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("p(z|C,%u) = ",iTrack);

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+1.3e ",obj->array[iTrack * obj->nPots + iPot]);

            }

            printf("\n");

        }

    }
