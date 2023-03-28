   
   /**
    * \file     target.c
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
    
    #include <signal/target.h>

    targets_obj * targets_construct_zero(const unsigned int nTargets) {

        targets_obj * obj;
        unsigned int iTarget;

        obj = (targets_obj *) malloc(sizeof(targets_obj));

        obj->nTargets = nTargets;
        
        obj->tags = (char **) malloc(sizeof(char *) * nTargets);

        for (iTarget = 0; iTarget < nTargets; iTarget++) {

            obj->tags[iTarget] = (char *) malloc(sizeof(char) * 256);
            strcpy(obj->tags[iTarget], "");

        }

        obj->array = (float *) malloc(sizeof(float) * 3 * nTargets);
        memset(obj->array, 0x00, sizeof(float) * 3 * nTargets);

        return obj;

    }

    void targets_destroy(targets_obj * obj) {

        unsigned int iTarget;

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {
            free((void *) obj->tags[iTarget]);
        }
        free((void *) obj->tags);

        free((void *) obj->array);
        free((void *) obj);

    }

    targets_obj * targets_clone(const targets_obj * obj) {

        targets_obj * clone;
        unsigned int iTarget;

        clone = (targets_obj *) malloc(sizeof(targets_obj));

        clone->nTargets = obj->nTargets;
        clone->array = (float *) malloc(sizeof(float) * 3 * obj->nTargets);
        memcpy(clone->array, obj->array, sizeof(float) * 3 * obj->nTargets);
        
        clone->tags = (char **) malloc(sizeof(char *) * obj->nTargets);

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

            clone->tags[iTarget] = (char *) malloc(sizeof(char) * 256);
            strcpy(clone->tags[iTarget], obj->tags[iTarget]);
            
        }

        return clone;

    }

    void targets_copy(targets_obj * dest, const targets_obj * src) {

        unsigned int iTarget;

        dest->nTargets = src->nTargets;
        memcpy(dest->array, src->array, sizeof(float) * 3 * src->nTargets);
        
        for (iTarget = 0; iTarget < src->nTargets; iTarget++) {

            strcpy(dest->tags[iTarget], src->tags[iTarget]);

        }

    }

    void targets_zero(targets_obj * obj) {

        unsigned int iTarget;

        memset(obj->array, 0x00, sizeof(float) * 3 * obj->nTargets);
        
        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {
            
            strcpy(obj->tags[iTarget], "");

        }

    }

    void targets_printf(const targets_obj * obj) {

        unsigned int iTarget;

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

            printf("[%s]: %+1.3f %+1.3f %+1.3f\n",
                   obj->tags[iTarget],
                   obj->array[iTarget * 3 + 0],
                   obj->array[iTarget * 3 + 1],
                   obj->array[iTarget * 3 + 2]);
            
        }

    }
