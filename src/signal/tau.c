   
   /**
    * \file     tau.c
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
    
    #include <signal/tau.h>

    taus_obj * taus_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        taus_obj * obj;

        obj = (taus_obj *) malloc(sizeof(taus_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->mu = (float *) malloc(sizeof(float) * nPoints * nPairs);
        memset(obj->mu, 0x00, sizeof(float) * nPoints * nPairs);

        obj->sigma2 = (float *) malloc(sizeof(float) * nPoints * nPairs);
        memset(obj->sigma2, 0x00, sizeof(float) * nPoints * nPairs);

        return obj;

    }

    void taus_destroy(taus_obj * obj) {

        free((void *) obj->mu);
        free((void *) obj->sigma2);

        free((void *) obj);

    }

    void taus_printf(const taus_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                printf("%03.3f (%03.3f) ",obj->mu[iPoint * obj->nPairs + iPair],obj->sigma2[iPoint * obj->nPairs + iPair]);

            }

            printf("\n");

        }

    }
