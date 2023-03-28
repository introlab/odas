   
   /**
    * \file     triangle.c
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
    
    #include <signal/triangle.h>

    triangles_obj * triangles_construct_zero(const unsigned int nTriangles) {

        triangles_obj * obj;

        obj = (triangles_obj *) malloc(sizeof(triangles_obj));

        obj->nTriangles = nTriangles;
        obj->array = (float *) malloc(sizeof(float) * nTriangles * 9);
        memset(obj->array, nTriangles * 9, sizeof(float));

        return obj;

    }

    void triangles_destroy(triangles_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void triangles_printf(const triangles_obj * obj) {

        unsigned int iTriangle;

        for (iTriangle = 0; iTriangle < obj->nTriangles; iTriangle++) {

            printf("(%04u): (%+1.3f,%+1.3f,%+1.3f) - (%+1.3f,%+1.3f,%+1.3f) - (%+1.3f,%+1.3f,%+1.3f)\n",
                   iTriangle,
                   obj->array[iTriangle * 9 + 0],
                   obj->array[iTriangle * 9 + 1],
                   obj->array[iTriangle * 9 + 2],
                   obj->array[iTriangle * 9 + 3],
                   obj->array[iTriangle * 9 + 4],
                   obj->array[iTriangle * 9 + 5],
                   obj->array[iTriangle * 9 + 6],
                   obj->array[iTriangle * 9 + 7],
                   obj->array[iTriangle * 9 + 8]);

        }

    }
