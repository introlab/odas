   
   /**
    * \file     point.c
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
