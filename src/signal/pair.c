   
   /**
    * \file     pair.c
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

    #include <signal/pair.h>

    pairs_obj * pairs_construct_zero(const unsigned int nPairs) {

        pairs_obj * obj;

        obj = (pairs_obj *) malloc(sizeof(pairs_obj));

        obj->nPairs = nPairs;
        obj->array = (char *) malloc(sizeof(char) * nPairs);
        memset(obj->array, 0x00, sizeof(char) * nPairs);

        return obj;

    }

    pairs_obj * pairs_clone(const pairs_obj * obj) {

        pairs_obj * clone;

        clone = (pairs_obj *) malloc(sizeof(pairs_obj));

        clone->nPairs = obj->nPairs;
        clone->array = (char *) malloc(sizeof(char) * obj->nPairs);
        memcpy(clone->array, obj->array, sizeof(char) * obj->nPairs);        

        return clone;

    }

    void pairs_destroy(pairs_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pairs_printf(const pairs_obj * obj) {

        unsigned int iPair;

        printf("nPairs: %u\n", obj->nPairs);
        
        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            printf("(%02u): %d\n", iPair, obj->array[iPair]);    
        }

    }
