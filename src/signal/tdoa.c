   
   /**
    * \file     tdoa.c
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
    
    #include <signal/tdoa.h>

    tdoas_obj * tdoas_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        tdoas_obj * obj;

        obj = (tdoas_obj *) malloc(sizeof(tdoas_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPoints * nPairs);

        obj->min = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->min, 0x00, sizeof(unsigned int) * nPairs);

        obj->max = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->max, 0x00, sizeof(unsigned int) * nPairs);

        return obj;

    }

    void tdoas_destroy(tdoas_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->min);
        free((void *) obj->max);
        free((void *) obj);

    }

    void tdoas_printf(const tdoas_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                printf("%04u ",obj->array[iPoint * obj->nPairs + iPair]);

            }

            printf("\n");

        }

        printf("(min): ");

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("%04u ",obj->min[iPair]);

        }

        printf("\n");

        printf("(max): ");

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("%04u ",obj->max[iPair]);

        }

        printf("\n");

    }
