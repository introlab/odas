   
   /**
    * \file     postprob.c
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

    #include <signal/postprob.h>

    postprobs_obj * postprobs_construct_zero(const unsigned int nPots, const unsigned int nTracks) {

        postprobs_obj * obj;

        obj = (postprobs_obj *) malloc(sizeof(postprobs_obj));

        obj->nPots = nPots;
        obj->nTracks = nTracks;

        obj->arrayNew = (float *) malloc(sizeof(float) * nPots);
        memset(obj->arrayNew, 0x00, sizeof(float) * nPots);

        obj->arrayTrack = (float *) malloc(sizeof(float) * nTracks * nPots);
        memset(obj->arrayTrack, 0x00, sizeof(float) * nTracks * nPots);

        obj->arrayTrackTotal = (float *) malloc(sizeof(float) * nTracks);
        memset(obj->arrayTrackTotal, 0x00, sizeof(float) * nTracks);        
        
        return obj;

    }    

    void postprobs_destroy(postprobs_obj * obj) {

        free((void *) obj->arrayNew);
        free((void *) obj->arrayTrack);
        free((void *) obj->arrayTrackTotal);
        free((void *) obj);

    }

    void postprobs_printf(const postprobs_obj * obj) {

        unsigned int iTrack;
        unsigned int iPot;

        printf("p(new|E,z): ");

        for (iPot = 0; iPot < obj->nPots; iPot++) {
        
            printf("%+1.3e ",obj->arrayNew[iPot]);

        }

        printf("\n");

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("  p(%u|E,z): ",iTrack);

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+1.3e ",obj->arrayTrack[iTrack * obj->nPots + iPot]);

            }

            printf("> %+1.3f\n",obj->arrayTrackTotal[iTrack]);

        }

    }
