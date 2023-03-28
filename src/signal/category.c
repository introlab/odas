
   /**
    * \file     category.c
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
    
    #include <signal/category.h>

    categories_obj * categories_construct_zero(const unsigned int nSignals) {

        categories_obj * obj;

        obj = (categories_obj *) malloc(sizeof(categories_obj));

        obj->nSignals = nSignals;
        obj->array = (char *) malloc(sizeof(char) * nSignals);
        memset(obj->array, 0x00, sizeof(char) * nSignals);

        return obj;

    }

    void categories_destroy(categories_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void categories_copy(categories_obj * dest, const categories_obj * src) {

        memcpy(dest->array, src->array, sizeof(char) * src->nSignals);

    }

    void categories_zero(categories_obj * obj) {

        memset(obj->array, 0x00, sizeof(char) * obj->nSignals);

    }

    void categories_printf(const categories_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %c\n",iSignal,obj->array[iSignal]);

        }

    }
