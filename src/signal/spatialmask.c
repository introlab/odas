   
   /**
    * \file     spatialmask.c
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
    
    #include <signal/spatialmask.h>

    spatialmasks_obj * spatialmasks_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        spatialmasks_obj * obj;

        obj = (spatialmasks_obj *) malloc(sizeof(spatialmasks_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->array = (char *) malloc(sizeof(char) * nPoints * nPairs);
        memset(obj->array, 0x00, sizeof(char) * nPoints * nPairs);

        return obj;

    }

    spatialmasks_obj * spatialmasks_clone(const spatialmasks_obj * obj) {

        spatialmasks_obj * clone;

        clone = (spatialmasks_obj *) malloc(sizeof(spatialmasks_obj));

        clone->nPoints = obj->nPoints;
        clone->nPairs = obj->nPairs;

        clone->array = (char *) malloc(sizeof(char) * obj->nPoints * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(char) * obj->nPoints * obj->nPairs);

        return clone;

    }

    void spatialmasks_destroy(spatialmasks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void spatialmasks_printf(const spatialmasks_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                if (obj->array[iPoint * obj->nPairs + iPair] != 0x00) {

                    printf("1");

                }
                else {

                    printf("0");

                }

            }

            printf("\n");            

        }

    }
