   
   /**
    * \file     point.c
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
    
    #include <signal/point.h>

    points_obj * points_construct_zero(const unsigned int nPoints) {

        points_obj * obj;

        obj = (points_obj *) malloc(sizeof(points_obj));

        obj->nPoints = nPoints;
        obj->array = (float *) malloc(sizeof(float) * nPoints * 3);
        memset(obj->array, 0x00, nPoints * 3 * sizeof(float));

        return obj;

    }

    points_obj * points_clone(const points_obj * obj) {

        points_obj * clone;

        clone = (points_obj *) malloc(sizeof(points_obj));

        clone->nPoints = obj->nPoints;
        clone->array = (float *) malloc(sizeof(float) * obj->nPoints * 3);
        memcpy(clone->array, obj->array, obj->nPoints * 3 * sizeof(float));

        return clone;

    }

    void points_destroy(points_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void points_printf(const points_obj * obj) {

        unsigned int iPoint;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): (%+1.3f,%+1.3f,%+1.3f)\n",
                   iPoint,
                   obj->array[iPoint * 3 + 0],
                   obj->array[iPoint * 3 + 1],
                   obj->array[iPoint * 3 + 2]);

        }

    }
