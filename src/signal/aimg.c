
   /**
    * \file     aimg.c
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
    
    #include <signal/aimg.h>

    aimg_obj * aimg_construct_zero(const unsigned int aimgSize) {

        aimg_obj * obj;

        obj = (aimg_obj *) malloc(sizeof(aimg_obj));

        obj->aimgSize = aimgSize;
        obj->array = (float *) malloc(sizeof(float) * aimgSize);
        memset(obj->array, 0x00, aimgSize * sizeof(float));       

        return obj;

    }

    void aimg_destroy(aimg_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void aimg_printf(const aimg_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSample = 0; iSample < obj->aimgSize; iSample++) {

            printf("%+1.5f ",obj->array[iSample]);

            if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->aimgSize)) {
                printf("\n");
            }

        }

        printf("\n");

    }
