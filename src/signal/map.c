   
   /**
    * \file     map.c
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

    #include <signal/map.h>

    maps_obj * maps_construct_zero(const unsigned int nCoarses, const unsigned int nFines) {

        maps_obj * obj;

        obj = (maps_obj *) malloc(sizeof(maps_obj));

        obj->nCoarses = nCoarses;
        obj->nFines = nFines;
        
        obj->array = (char *) malloc(sizeof(char) * nFines * nCoarses);
        memset(obj->array, 0x00, sizeof(char) * nFines * nCoarses);

        return obj;

    }

    void maps_destroy(maps_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void maps_printf(const maps_obj * obj) {

        unsigned int iFine;
        unsigned int iCoarse;

        for (iFine = 0; iFine < obj->nFines; iFine++) {

            printf("(%04u): ",iFine);

            for (iCoarse = 0; iCoarse < obj->nCoarses; iCoarse++) {

                printf("%01u",obj->array[iFine * obj->nCoarses + iCoarse]);

            }

            printf("\n");

        }

    }
