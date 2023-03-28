   
   /**
    * \file     transcendental.c
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
    
    #include <utils/transcendental.h>

    transcendental_obj * transcendental_construct_zero(const float minValue, const float maxValue, const unsigned int nElements) {

        transcendental_obj * obj;
        unsigned int iElement;
        float v;
        float g;
        float intPart;
        float fracPart; 

        const float table[21] = {0.75008f,0.93640f,1.11688f,1.28852f,1.45013f,1.60184f,1.74422f,
                                 1.87812f,2.00448f,2.12417f,2.23799f,2.34656f,2.45053f,2.55031f,
                                 2.64646f,2.73921f,2.82895f,2.91602f,3.00049f,3.08265f,3.16270f};

        obj = (transcendental_obj *) malloc(sizeof(transcendental_obj));

        obj->minValue = minValue;
        obj->maxValue = maxValue;
        obj->interval = (maxValue-minValue) / ((float) (nElements-1));

        obj->array = (float *) malloc(sizeof(float) * nElements);
        memset(obj->array, 0x00, sizeof(float) * nElements);

        obj->nElements = nElements;

        v = 0.0f;

        for (iElement = 0; iElement < nElements; iElement++) {

            if (v <= 9.5f) {

                intPart = floorf(2.0f * v);
                fracPart = 2.0f * v - intPart;

                g = ((1-fracPart) * table[((unsigned int) intPart)] + fracPart * table[((unsigned int) intPart) + 1]) / sqrtf(v + 0.0001f);

            }
            else {

                g = 1.0f;
                
            }

            obj->array[iElement] = g;

            v += obj->interval;

        }

        return obj;

    }

    void transcendental_destroy(transcendental_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    float transcendental_process(const transcendental_obj * obj, const float value) {

        signed int iElement;

        iElement = ((signed int) floorf(value / obj->interval)) + 1;

        if (iElement < 0) {
            iElement = 0;
        }
        if (iElement > (obj->nElements - 1)) {
            iElement = obj->nElements - 1;
        }

        return obj->array[iElement];

    }
