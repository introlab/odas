   
   /**
    * \file     spatialindex.c
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

    #include <signal/spatialindex.h>

    spatialindexes_obj * spatialindexes_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        spatialindexes_obj * obj;

        obj = (spatialindexes_obj *) malloc(sizeof(spatialindexes_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;
        
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPoints * nPairs);

        obj->count = (unsigned int *) malloc(sizeof(unsigned int) * nPoints);
        memset(obj->count, 0x00, sizeof(unsigned int) * nPoints);

        return obj;

    }

    spatialindexes_obj * spatialindexes_clone(const spatialindexes_obj * obj) {

        spatialindexes_obj * clone;

        clone = (spatialindexes_obj *) malloc(sizeof(spatialindexes_obj));

        clone->nPoints = obj->nPoints;
        clone->nPairs = obj->nPairs;

        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPoints * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nPoints * obj->nPairs);

        clone->count = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPoints);
        memcpy(clone->count, obj->count, sizeof(unsigned int) * obj->nPoints);

        return clone;

    }

    void spatialindexes_destroy(spatialindexes_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->count);

        free((void *) obj);

    }

    void spatialindexes_printf(const spatialindexes_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            if (obj->count[iPoint] > 0) {

                for (iPair = 0; iPair < obj->count[iPoint]; iPair++) {

                    printf("%03u ",obj->array[iPoint * obj->nPairs + iPair]);

                }

            }
            else {

                printf("-");

            }

            printf("\n");

        }

    }
