   
   /**
    * \file     spatialgain.c
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
    
    #include <signal/spatialgain.h>

    spatialgains_obj * spatialgains_construct_zero(const unsigned int nChannels, const unsigned int nPoints) {

        spatialgains_obj * obj;

        obj = (spatialgains_obj *) malloc(sizeof(spatialgains_obj));

        obj->nChannels = nChannels;
        obj->nPoints = nPoints;

        obj->array = (float *) malloc(sizeof(float) * nChannels * nPoints);
        memset(obj->array, 0x00, sizeof(float) * nChannels * nPoints);

        return obj;

    }

    spatialgains_obj * spatialgains_clone(const spatialgains_obj * obj) {

        spatialgains_obj * clone;

        clone = (spatialgains_obj *) malloc(sizeof(spatialgains_obj));

        clone->nChannels = obj->nChannels;
        clone->nPoints = obj->nPoints;

        clone->array = (float *) malloc(sizeof(float) * obj->nChannels * obj->nPoints);
        memcpy(clone->array, obj->array, sizeof(float) * obj->nChannels * obj->nPoints);

        return clone;

    }

    void spatialgains_destroy(spatialgains_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void spatialgains_printf(const spatialgains_obj * obj) {

        unsigned int iPoint;
        unsigned int iChannel;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%1.2f ",obj->array[iPoint * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }
