
   /**
    * \file     delta.c
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

    #include <signal/delta.h>

    deltas_obj * deltas_construct_zero(const unsigned int nPairs) {

        deltas_obj * obj;

        obj = (deltas_obj *) malloc(sizeof(deltas_obj));

        obj->nPairs = nPairs;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);
        memset(obj->array, 0x00, sizeof(unsigned int) * nPairs);

        return obj;

    }

    deltas_obj * deltas_clone(const deltas_obj * obj) {

        deltas_obj * clone;

        clone = (deltas_obj *) malloc(sizeof(deltas_obj));

        clone->nPairs = obj->nPairs;
        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nPairs);

        return clone;

    }

    void deltas_destroy(deltas_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void deltas_printf(const deltas_obj * obj) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("(%02u): %02u\n",iPair,obj->array[iPair]);

        }

    }
