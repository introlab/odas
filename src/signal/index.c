   
   /**
    * \file     index.c
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
    
    #include <signal/index.h>

    indexes_obj * indexes_construct_zero(const unsigned int nCoarses, const unsigned int nFines) {

        indexes_obj * obj;

        obj = (indexes_obj *) malloc(sizeof(indexes_obj));

        obj->nCoarses = nCoarses;
        obj->nFines = nFines;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nCoarses * nFines);
        memset(obj->array, 0x00, sizeof(unsigned int) * nCoarses * nFines);
        obj->count = (unsigned int *) malloc(sizeof(unsigned int) * nCoarses);
        memset(obj->count, 0x00, sizeof(unsigned int) * nCoarses);

        return obj;

    }

    void indexes_destroy(indexes_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->count);
        free((void *) obj);

    }

    void indexes_printf(const indexes_obj * obj) {

        unsigned int iCoarse;
        unsigned int iFine;

        for (iCoarse = 0; iCoarse < obj->nCoarses; iCoarse++) {

            printf("(%04u): ",iCoarse);

            if (obj->count[iCoarse] > 0) {

                for (iFine = 0; iFine < obj->count[iCoarse]; iFine++) {

                    printf("%04u ",obj->array[iCoarse * obj->nFines + iFine]);

                }

            }
            else {

                printf("-");

            }

            printf("\n");

        }

    }
