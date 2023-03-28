   
   /**
    * \file     tau.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
