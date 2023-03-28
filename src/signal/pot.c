   
   /**
    * \file     pot.c
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
    
    #include <signal/pot.h>

    pots_obj * pots_construct_zero(const unsigned int nPots) {

        pots_obj * obj;

        obj = (pots_obj *) malloc(sizeof(pots_obj));

        obj->nPots = nPots;
        obj->array = (float *) malloc(sizeof(float) * 4 * nPots);
        memset(obj->array, 0x00, sizeof(float) * 4 * nPots);

        return obj;

    }

    pots_obj * pots_clone(const pots_obj * obj) {

      pots_obj * clone;

      clone = (pots_obj *) malloc(sizeof(pots_obj));

      clone->nPots = obj->nPots;
      clone->array = (float *) malloc(sizeof(float) * 4 * obj->nPots);
      memcpy(clone->array, obj->array, sizeof(float) * 4 * obj->nPots);

      return clone;

    }

    void pots_copy(pots_obj * dest, const pots_obj * src) {

      dest->nPots = src->nPots;

      memcpy(dest->array, src->array, sizeof(float) * 4 * src->nPots);

    }

    void pots_zero(pots_obj * obj) {

      obj->nPots = 0;
      memset(obj->array, 0x00, sizeof(float) * 4 * obj->nPots);

    }

    void pots_destroy(pots_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pots_printf(const pots_obj * obj) {

        unsigned int iPot;

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            printf("(%02u): %+1.3f %+1.3f %+1.3f %+1.3f\n",
                   iPot,
                   obj->array[iPot * 4 + 0],
                   obj->array[iPot * 4 + 1],
                   obj->array[iPot * 4 + 2],
                   obj->array[iPot * 4 + 3]);
            
        }

    }
