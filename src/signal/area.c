
   /**
    * \file     area.c
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
    
    #include <signal/area.h>

    areas_obj * areas_construct_zero(const unsigned int nPointsDiscrete, const unsigned int nResolutionsPerDiscrete, const unsigned int nPairs) {

        areas_obj * obj;

        obj = (areas_obj *) malloc(sizeof(areas_obj));

        obj->nPointsDiscrete = nPointsDiscrete;
        obj->nResolutionsPerDiscrete = nResolutionsPerDiscrete;
        obj->nPairs = nPairs;

        obj->array = (float *) malloc(sizeof(float) * nPointsDiscrete * nResolutionsPerDiscrete * nPairs);
        memset(obj->array, 0x00, sizeof(float) * nPointsDiscrete * nResolutionsPerDiscrete * nPairs);

        return obj;

    }

    void areas_destroy(areas_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void areas_printf(const areas_obj * obj) {

        unsigned int iPointDiscrete;
        unsigned int iResolutionPerDiscrete;
        unsigned int iPair;

        printf("%u\n",obj->nPointsDiscrete);
        printf("%u\n",obj->nResolutionsPerDiscrete);
        printf("%u\n",obj->nPairs);

        for (iPointDiscrete = 0; iPointDiscrete < obj->nPointsDiscrete; iPointDiscrete++) {

            for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < obj->nResolutionsPerDiscrete; iResolutionPerDiscrete++) {

                printf("(%04u:%03u): ", iPointDiscrete, iResolutionPerDiscrete);

                for (iPair = 0; iPair < obj->nPairs; iPair++) {

                    printf("%1.1E ",obj->array[iPointDiscrete * (obj->nResolutionsPerDiscrete * obj->nPairs) + iResolutionPerDiscrete * obj->nPairs + iPair]);

                }

                printf("\n");

            }

        }

    }

    area_obj * area_construct_zero(const unsigned int nPairs) {

        area_obj * obj;        

        obj = (area_obj *) malloc(sizeof(area_obj));

        obj->nPairs = nPairs;

        obj->array = (float *) malloc(sizeof(float) * nPairs);
        memset(obj->array, 0x00, sizeof(float) * nPairs);

        return obj;

    }

    void area_destroy(area_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void area_printf(const area_obj * obj) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            printf("(%03u): %+1.3f\n", iPair, obj->array[iPair]);

        }        

    }
