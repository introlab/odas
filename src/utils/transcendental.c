   
   /**
    * \file     transcendental.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
