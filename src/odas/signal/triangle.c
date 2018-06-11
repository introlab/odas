   
   /**
    * \file     triangle.c
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
