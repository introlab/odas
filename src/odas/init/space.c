
   /**
    * \file     space.c
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

    #include <init/space.h>

    triangles_obj * space_triangles_level_zero(void) {

        points_obj * points;
        triangles_obj * triangles;
        
        unsigned int iPoint;
        unsigned int iTriangle;

        float h,r;

        h = sqrtf(5.0f)/5.0f;
        r = (2.0f/5.0f)*sqrtf(5.0f);

        points = points_construct_zero(12);

        points->array[0 * 3 + 0] = 0.0f;
        points->array[0 * 3 + 1] = 0.0f;
        points->array[0 * 3 + 2] = 1.0f;
        points->array[11 * 3 + 0] = 0.0f;
        points->array[11 * 3 + 1] = 0.0f;
        points->array[11 * 3 + 2] = -1.0f;

        for (iPoint = 0; iPoint < 5; iPoint++) {

            points->array[(iPoint+1) * 3 + 0] = r * sinf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+1) * 3 + 1] = r * cosf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+1) * 3 + 2] = h;

            points->array[(iPoint+6) * 3 + 0] = -1.0f * r * sinf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+6) * 3 + 1] = -1.0f * r * cosf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+6) * 3 + 2] = -1.0f * h;

        }        

        triangles = triangles_construct_zero(20);

        // Triangle 0: Points 0, 2, 1
        triangles->array[0 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[0 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[0 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[0 * 9 + 3] = points->array[2 * 3 + 0];
        triangles->array[0 * 9 + 4] = points->array[2 * 3 + 1];
        triangles->array[0 * 9 + 5] = points->array[2 * 3 + 2];
        triangles->array[0 * 9 + 6] = points->array[1 * 3 + 0];
        triangles->array[0 * 9 + 7] = points->array[1 * 3 + 1];
        triangles->array[0 * 9 + 8] = points->array[1 * 3 + 2];

        // Triangle 1: Points 0, 3, 2
        triangles->array[1 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[1 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[1 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[1 * 9 + 3] = points->array[3 * 3 + 0];
        triangles->array[1 * 9 + 4] = points->array[3 * 3 + 1];
        triangles->array[1 * 9 + 5] = points->array[3 * 3 + 2];
        triangles->array[1 * 9 + 6] = points->array[2 * 3 + 0];
        triangles->array[1 * 9 + 7] = points->array[2 * 3 + 1];
        triangles->array[1 * 9 + 8] = points->array[2 * 3 + 2];

        // Triangle 2: Points 0, 4, 3
        triangles->array[2 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[2 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[2 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[2 * 9 + 3] = points->array[4 * 3 + 0];
        triangles->array[2 * 9 + 4] = points->array[4 * 3 + 1];
        triangles->array[2 * 9 + 5] = points->array[4 * 3 + 2];
        triangles->array[2 * 9 + 6] = points->array[3 * 3 + 0];
        triangles->array[2 * 9 + 7] = points->array[3 * 3 + 1];
        triangles->array[2 * 9 + 8] = points->array[3 * 3 + 2];
        
        // Triangle 3: Points 0, 5, 4
        triangles->array[3 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[3 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[3 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[3 * 9 + 3] = points->array[5 * 3 + 0];
        triangles->array[3 * 9 + 4] = points->array[5 * 3 + 1];
        triangles->array[3 * 9 + 5] = points->array[5 * 3 + 2];
        triangles->array[3 * 9 + 6] = points->array[4 * 3 + 0];
        triangles->array[3 * 9 + 7] = points->array[4 * 3 + 1];
        triangles->array[3 * 9 + 8] = points->array[4 * 3 + 2];

        // Triangle 4: Points 0, 1, 5
        triangles->array[4 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[4 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[4 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[4 * 9 + 3] = points->array[1 * 3 + 0];
        triangles->array[4 * 9 + 4] = points->array[1 * 3 + 1];
        triangles->array[4 * 9 + 5] = points->array[1 * 3 + 2];
        triangles->array[4 * 9 + 6] = points->array[5 * 3 + 0];
        triangles->array[4 * 9 + 7] = points->array[5 * 3 + 1];
        triangles->array[4 * 9 + 8] = points->array[5 * 3 + 2];

        // Triangle 5: Points 9, 1, 2
        triangles->array[5 * 9 + 0] = points->array[9 * 3 + 0];
        triangles->array[5 * 9 + 1] = points->array[9 * 3 + 1];
        triangles->array[5 * 9 + 2] = points->array[9 * 3 + 2];
        triangles->array[5 * 9 + 3] = points->array[1 * 3 + 0];
        triangles->array[5 * 9 + 4] = points->array[1 * 3 + 1];
        triangles->array[5 * 9 + 5] = points->array[1 * 3 + 2];
        triangles->array[5 * 9 + 6] = points->array[2 * 3 + 0];
        triangles->array[5 * 9 + 7] = points->array[2 * 3 + 1];
        triangles->array[5 * 9 + 8] = points->array[2 * 3 + 2];

        // Triangle 6: Points 10, 2, 3
        triangles->array[6 * 9 + 0] = points->array[10 * 3 + 0];
        triangles->array[6 * 9 + 1] = points->array[10 * 3 + 1];
        triangles->array[6 * 9 + 2] = points->array[10 * 3 + 2];
        triangles->array[6 * 9 + 3] = points->array[2 * 3 + 0];
        triangles->array[6 * 9 + 4] = points->array[2 * 3 + 1];
        triangles->array[6 * 9 + 5] = points->array[2 * 3 + 2];
        triangles->array[6 * 9 + 6] = points->array[3 * 3 + 0];
        triangles->array[6 * 9 + 7] = points->array[3 * 3 + 1];
        triangles->array[6 * 9 + 8] = points->array[3 * 3 + 2];

        // Triangle 7: Points 6, 3, 4
        triangles->array[7 * 9 + 0] = points->array[6 * 3 + 0];
        triangles->array[7 * 9 + 1] = points->array[6 * 3 + 1];
        triangles->array[7 * 9 + 2] = points->array[6 * 3 + 2];
        triangles->array[7 * 9 + 3] = points->array[3 * 3 + 0];
        triangles->array[7 * 9 + 4] = points->array[3 * 3 + 1];
        triangles->array[7 * 9 + 5] = points->array[3 * 3 + 2];
        triangles->array[7 * 9 + 6] = points->array[4 * 3 + 0];
        triangles->array[7 * 9 + 7] = points->array[4 * 3 + 1];
        triangles->array[7 * 9 + 8] = points->array[4 * 3 + 2];
        
        // Triangle 8: Points 7, 4, 5
        triangles->array[8 * 9 + 0] = points->array[7 * 3 + 0];
        triangles->array[8 * 9 + 1] = points->array[7 * 3 + 1];
        triangles->array[8 * 9 + 2] = points->array[7 * 3 + 2];
        triangles->array[8 * 9 + 3] = points->array[4 * 3 + 0];
        triangles->array[8 * 9 + 4] = points->array[4 * 3 + 1];
        triangles->array[8 * 9 + 5] = points->array[4 * 3 + 2];
        triangles->array[8 * 9 + 6] = points->array[5 * 3 + 0];
        triangles->array[8 * 9 + 7] = points->array[5 * 3 + 1];
        triangles->array[8 * 9 + 8] = points->array[5 * 3 + 2];

        // Triangle 9: Points 8, 5, 1
        triangles->array[9 * 9 + 0] = points->array[8 * 3 + 0];
        triangles->array[9 * 9 + 1] = points->array[8 * 3 + 1];
        triangles->array[9 * 9 + 2] = points->array[8 * 3 + 2];
        triangles->array[9 * 9 + 3] = points->array[5 * 3 + 0];
        triangles->array[9 * 9 + 4] = points->array[5 * 3 + 1];
        triangles->array[9 * 9 + 5] = points->array[5 * 3 + 2];
        triangles->array[9 * 9 + 6] = points->array[1 * 3 + 0];
        triangles->array[9 * 9 + 7] = points->array[1 * 3 + 1];
        triangles->array[9 * 9 + 8] = points->array[1 * 3 + 2];

        // Triangle 10: Points 4, 7, 6
        triangles->array[10 * 9 + 0] = points->array[4 * 3 + 0];
        triangles->array[10 * 9 + 1] = points->array[4 * 3 + 1];
        triangles->array[10 * 9 + 2] = points->array[4 * 3 + 2];
        triangles->array[10 * 9 + 3] = points->array[7 * 3 + 0];
        triangles->array[10 * 9 + 4] = points->array[7 * 3 + 1];
        triangles->array[10 * 9 + 5] = points->array[7 * 3 + 2];
        triangles->array[10 * 9 + 6] = points->array[6 * 3 + 0];
        triangles->array[10 * 9 + 7] = points->array[6 * 3 + 1];
        triangles->array[10 * 9 + 8] = points->array[6 * 3 + 2];
        
        // Triangle 11: Points 5, 8, 7
        triangles->array[11 * 9 + 0] = points->array[5 * 3 + 0];
        triangles->array[11 * 9 + 1] = points->array[5 * 3 + 1];
        triangles->array[11 * 9 + 2] = points->array[5 * 3 + 2];
        triangles->array[11 * 9 + 3] = points->array[8 * 3 + 0];
        triangles->array[11 * 9 + 4] = points->array[8 * 3 + 1];
        triangles->array[11 * 9 + 5] = points->array[8 * 3 + 2];
        triangles->array[11 * 9 + 6] = points->array[7 * 3 + 0];
        triangles->array[11 * 9 + 7] = points->array[7 * 3 + 1];
        triangles->array[11 * 9 + 8] = points->array[7 * 3 + 2];
        
        // Triangle 12: Points 1, 9, 8
        triangles->array[12 * 9 + 0] = points->array[1 * 3 + 0];
        triangles->array[12 * 9 + 1] = points->array[1 * 3 + 1];
        triangles->array[12 * 9 + 2] = points->array[1 * 3 + 2];
        triangles->array[12 * 9 + 3] = points->array[9 * 3 + 0];
        triangles->array[12 * 9 + 4] = points->array[9 * 3 + 1];
        triangles->array[12 * 9 + 5] = points->array[9 * 3 + 2];
        triangles->array[12 * 9 + 6] = points->array[8 * 3 + 0];
        triangles->array[12 * 9 + 7] = points->array[8 * 3 + 1];
        triangles->array[12 * 9 + 8] = points->array[8 * 3 + 2];

        // Triangle 13: Points 2, 10, 9
        triangles->array[13 * 9 + 0] = points->array[2 * 3 + 0];
        triangles->array[13 * 9 + 1] = points->array[2 * 3 + 1];
        triangles->array[13 * 9 + 2] = points->array[2 * 3 + 2];
        triangles->array[13 * 9 + 3] = points->array[10 * 3 + 0];
        triangles->array[13 * 9 + 4] = points->array[10 * 3 + 1];
        triangles->array[13 * 9 + 5] = points->array[10 * 3 + 2];
        triangles->array[13 * 9 + 6] = points->array[9 * 3 + 0];
        triangles->array[13 * 9 + 7] = points->array[9 * 3 + 1];
        triangles->array[13 * 9 + 8] = points->array[9 * 3 + 2];

        // Triangle 14: Points 3, 6, 10
        triangles->array[14 * 9 + 0] = points->array[3 * 3 + 0];
        triangles->array[14 * 9 + 1] = points->array[3 * 3 + 1];
        triangles->array[14 * 9 + 2] = points->array[3 * 3 + 2];
        triangles->array[14 * 9 + 3] = points->array[6 * 3 + 0];
        triangles->array[14 * 9 + 4] = points->array[6 * 3 + 1];
        triangles->array[14 * 9 + 5] = points->array[6 * 3 + 2];
        triangles->array[14 * 9 + 6] = points->array[10 * 3 + 0];
        triangles->array[14 * 9 + 7] = points->array[10 * 3 + 1];
        triangles->array[14 * 9 + 8] = points->array[10 * 3 + 2];

        // Triangle 15: Points 11, 6, 7
        triangles->array[15 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[15 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[15 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[15 * 9 + 3] = points->array[6 * 3 + 0];
        triangles->array[15 * 9 + 4] = points->array[6 * 3 + 1];
        triangles->array[15 * 9 + 5] = points->array[6 * 3 + 2];
        triangles->array[15 * 9 + 6] = points->array[7 * 3 + 0];
        triangles->array[15 * 9 + 7] = points->array[7 * 3 + 1];
        triangles->array[15 * 9 + 8] = points->array[7 * 3 + 2];

        // Triangle 16: Points 11, 7, 8
        triangles->array[16 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[16 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[16 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[16 * 9 + 3] = points->array[7 * 3 + 0];
        triangles->array[16 * 9 + 4] = points->array[7 * 3 + 1];
        triangles->array[16 * 9 + 5] = points->array[7 * 3 + 2];
        triangles->array[16 * 9 + 6] = points->array[8 * 3 + 0];
        triangles->array[16 * 9 + 7] = points->array[8 * 3 + 1];
        triangles->array[16 * 9 + 8] = points->array[8 * 3 + 2];
        
        // Triangle 17: Points 11, 8, 9
        triangles->array[17 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[17 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[17 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[17 * 9 + 3] = points->array[8 * 3 + 0];
        triangles->array[17 * 9 + 4] = points->array[8 * 3 + 1];
        triangles->array[17 * 9 + 5] = points->array[8 * 3 + 2];
        triangles->array[17 * 9 + 6] = points->array[9 * 3 + 0];
        triangles->array[17 * 9 + 7] = points->array[9 * 3 + 1];
        triangles->array[17 * 9 + 8] = points->array[9 * 3 + 2];

        // Triangle 18: Points 11, 9, 10
        triangles->array[18 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[18 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[18 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[18 * 9 + 3] = points->array[9 * 3 + 0];
        triangles->array[18 * 9 + 4] = points->array[9 * 3 + 1];
        triangles->array[18 * 9 + 5] = points->array[9 * 3 + 2];
        triangles->array[18 * 9 + 6] = points->array[10 * 3 + 0];
        triangles->array[18 * 9 + 7] = points->array[10 * 3 + 1];
        triangles->array[18 * 9 + 8] = points->array[10 * 3 + 2];

        // Triangle 19: Points 11, 10, 6
        triangles->array[19 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[19 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[19 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[19 * 9 + 3] = points->array[10 * 3 + 0];
        triangles->array[19 * 9 + 4] = points->array[10 * 3 + 1];
        triangles->array[19 * 9 + 5] = points->array[10 * 3 + 2];
        triangles->array[19 * 9 + 6] = points->array[6 * 3 + 0];
        triangles->array[19 * 9 + 7] = points->array[6 * 3 + 1];
        triangles->array[19 * 9 + 8] = points->array[6 * 3 + 2];

        points_destroy(points);

        return triangles;

    }

    triangles_obj * space_triangles_level_next(const triangles_obj * triangles) {

        triangles_obj * obj;
        unsigned int iTriangle;

        float point1[3];
        float point2[3];
        float point3[3];
        float pointA[3];
        float pointB[3];
        float pointC[3];
        float norm1;
        float norm2;
        float norm3;

        obj = triangles_construct_zero(triangles->nTriangles * 4);

        for (iTriangle = 0; iTriangle < triangles->nTriangles; iTriangle++) {

            pointA[0] = triangles->array[iTriangle*9+0];
            pointA[1] = triangles->array[iTriangle*9+1];
            pointA[2] = triangles->array[iTriangle*9+2];
            pointB[0] = triangles->array[iTriangle*9+3];
            pointB[1] = triangles->array[iTriangle*9+4];
            pointB[2] = triangles->array[iTriangle*9+5];
            pointC[0] = triangles->array[iTriangle*9+6];
            pointC[1] = triangles->array[iTriangle*9+7];
            pointC[2] = triangles->array[iTriangle*9+8];

            point1[0] = pointA[0] + pointB[0];
            point1[1] = pointA[1] + pointB[1];
            point1[2] = pointA[2] + pointB[2];
            point2[0] = pointB[0] + pointC[0];
            point2[1] = pointB[1] + pointC[1];
            point2[2] = pointB[2] + pointC[2];
            point3[0] = pointC[0] + pointA[0];
            point3[1] = pointC[1] + pointA[1];
            point3[2] = pointC[2] + pointA[2];

            norm1 = sqrtf(point1[0] * point1[0] + point1[1] * point1[1] + point1[2] * point1[2]);
            norm2 = sqrtf(point2[0] * point2[0] + point2[1] * point2[1] + point2[2] * point2[2]);
            norm3 = sqrtf(point3[0] * point3[0] + point3[1] * point3[1] + point3[2] * point3[2]);

            point1[0] /= norm1;
            point1[1] /= norm1;
            point1[2] /= norm1;
            point2[0] /= norm2;
            point2[1] /= norm2;
            point2[2] /= norm2;
            point3[0] /= norm3;
            point3[1] /= norm3;
            point3[2] /= norm3;

            obj->array[(iTriangle*4+0)*9+0] = pointA[0];
            obj->array[(iTriangle*4+0)*9+1] = pointA[1];
            obj->array[(iTriangle*4+0)*9+2] = pointA[2];
            obj->array[(iTriangle*4+0)*9+3] = point1[0];
            obj->array[(iTriangle*4+0)*9+4] = point1[1];
            obj->array[(iTriangle*4+0)*9+5] = point1[2];
            obj->array[(iTriangle*4+0)*9+6] = point3[0];
            obj->array[(iTriangle*4+0)*9+7] = point3[1];
            obj->array[(iTriangle*4+0)*9+8] = point3[2];

            obj->array[(iTriangle*4+1)*9+0] = point1[0];
            obj->array[(iTriangle*4+1)*9+1] = point1[1];
            obj->array[(iTriangle*4+1)*9+2] = point1[2];
            obj->array[(iTriangle*4+1)*9+3] = pointB[0];
            obj->array[(iTriangle*4+1)*9+4] = pointB[1];
            obj->array[(iTriangle*4+1)*9+5] = pointB[2];
            obj->array[(iTriangle*4+1)*9+6] = point2[0];
            obj->array[(iTriangle*4+1)*9+7] = point2[1];
            obj->array[(iTriangle*4+1)*9+8] = point2[2];

            obj->array[(iTriangle*4+2)*9+0] = point1[0];
            obj->array[(iTriangle*4+2)*9+1] = point1[1];
            obj->array[(iTriangle*4+2)*9+2] = point1[2];
            obj->array[(iTriangle*4+2)*9+3] = point2[0];
            obj->array[(iTriangle*4+2)*9+4] = point2[1];
            obj->array[(iTriangle*4+2)*9+5] = point2[2];
            obj->array[(iTriangle*4+2)*9+6] = point3[0];
            obj->array[(iTriangle*4+2)*9+7] = point3[1];
            obj->array[(iTriangle*4+2)*9+8] = point3[2];      

            obj->array[(iTriangle*4+3)*9+0] = point3[0];
            obj->array[(iTriangle*4+3)*9+1] = point3[1];
            obj->array[(iTriangle*4+3)*9+2] = point3[2];
            obj->array[(iTriangle*4+3)*9+3] = point2[0];
            obj->array[(iTriangle*4+3)*9+4] = point2[1];
            obj->array[(iTriangle*4+3)*9+5] = point2[2];
            obj->array[(iTriangle*4+3)*9+6] = pointC[0];
            obj->array[(iTriangle*4+3)*9+7] = pointC[1];
            obj->array[(iTriangle*4+3)*9+8] = pointC[2];                     

        }

        return obj;

    }

    triangles_obj * space_triangles_level_level(const unsigned int level) {

        triangles_obj * obj;
        triangles_obj * triangles;
        unsigned int iLevel;

        obj = space_triangles_level_zero();

        for (iLevel = 0; iLevel < level; iLevel++) {
            triangles = space_triangles_level_next(obj);
            triangles_destroy(obj);
            obj = triangles;
        }

        return obj;

    }

    triangles_obj * space_triangles_points(const points_obj * points, const unsigned int index) {

        unsigned int iPoint;
        float x1, y1, z1;
        float x2, y2, z2;
        float dx, dy, dz;
        float dist, minDist;
        unsigned int iPointMin;
        float ux, uy, uz;
        float tx, ty, tz;
        float x0, y0, z0;
        float xR, yR, zR;
        unsigned int iAngle;
        unsigned int nAngles;
        float theta;
        float R11, R12, R13, R21, R22, R23, R31, R32, R33;
        float dot;
        float norm;

        triangles_obj * triangles_octo;
        points_obj * points_octo;

        x1 = points->array[index*3+0];
        y1 = points->array[index*3+1];
        z1 = points->array[index*3+2];

        minDist = +INFINITY;

        for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

            if (iPoint != index) {

                x2 = points->array[iPoint*3+0];
                y2 = points->array[iPoint*3+1];
                z2 = points->array[iPoint*3+2];

                dx = x1 - x2;
                dy = y1 - y2;
                dz = z1 - z2;

                dist = dx*dx + dy*dy + dz*dz;

                if (dist < minDist) {

                    minDist = dist;
                    iPointMin = iPoint;

                }

            }

        }

        ux = points->array[index*3+0];
        uy = points->array[index*3+1];
        uz = points->array[index*3+2];

        x1 = points->array[iPointMin*3+0];
        y1 = points->array[iPointMin*3+1];
        z1 = points->array[iPointMin*3+2];

        dot = (ux*x1) + (uy*y1) + (uz*z1);

        x0 = ux + x1 - dot * ux;
        y0 = uy + y1 - dot * uy;
        z0 = uz + z1 - dot * uz;

        /*
        tx = ux - x0;
        ty = uy - y0;
        tz = uz - z0;

        tx *= 0.75f;
        ty *= 0.75f;
        tz *= 0.75f;

        x0 = ux - tx;
        y0 = uy - ty;
        z0 = uz - tz;
        */

        nAngles = 8;

        points_octo = points_construct_zero(nAngles);

        for (iAngle = 0; iAngle < nAngles; iAngle++) {

            theta = 2*M_PI * ((float) iAngle) / ((float) nAngles);

            R11 = cosf(theta) + (ux*ux) * (1.0f - cosf(theta));
            R12 = (ux*uy) * (1.0f - cosf(theta)) - uz * sinf(theta);
            R13 = (ux*uz) * (1.0f - cosf(theta)) + uy * sinf(theta);
            R21 = (uy*ux) * (1.0f - cosf(theta)) + uz * sinf(theta);
            R22 = cosf(theta) + (uy*uy) * (1.0f - cosf(theta));
            R23 = (uy*uz) * (1.0f - cosf(theta)) - ux * sinf(theta);
            R31 = (uz*ux) * (1.0f - cosf(theta)) - uy * sinf(theta);
            R32 = (uz*uy) * (1.0f - cosf(theta)) + ux * sinf(theta);
            R33 = cosf(theta) + (uz*uz) * (1.0f - cosf(theta));

            xR = R11 * x0 + R12 * y0 + R13 * z0;
            yR = R21 * x0 + R22 * y0 + R23 * z0;
            zR = R31 * x0 + R32 * y0 + R33 * z0;

            norm = sqrtf(xR*xR + yR*yR + zR*zR);

            xR /= norm;
            yR /= norm;
            zR /= norm;

            points_octo->array[iAngle*3+0] = xR;
            points_octo->array[iAngle*3+1] = yR;
            points_octo->array[iAngle*3+2] = zR;

        }

        triangles_octo = triangles_construct_zero(nAngles);

        for (iAngle = 0; iAngle < (nAngles-1); iAngle++) {

            triangles_octo->array[iAngle*9+0] = points_octo->array[iAngle*3+0];
            triangles_octo->array[iAngle*9+1] = points_octo->array[iAngle*3+1];
            triangles_octo->array[iAngle*9+2] = points_octo->array[iAngle*3+2];
            triangles_octo->array[iAngle*9+3] = ux;
            triangles_octo->array[iAngle*9+4] = uy;
            triangles_octo->array[iAngle*9+5] = uz;
            triangles_octo->array[iAngle*9+6] = points_octo->array[(iAngle+1)*3+0];
            triangles_octo->array[iAngle*9+7] = points_octo->array[(iAngle+1)*3+1];
            triangles_octo->array[iAngle*9+8] = points_octo->array[(iAngle+1)*3+2];            

        }

        triangles_octo->array[iAngle*9+0] = points_octo->array[(nAngles-1)*3+0];
        triangles_octo->array[iAngle*9+1] = points_octo->array[(nAngles-1)*3+1];
        triangles_octo->array[iAngle*9+2] = points_octo->array[(nAngles-1)*3+2];
        triangles_octo->array[iAngle*9+3] = ux;
        triangles_octo->array[iAngle*9+4] = uy;
        triangles_octo->array[iAngle*9+5] = uz;
        triangles_octo->array[iAngle*9+6] = points_octo->array[0];
        triangles_octo->array[iAngle*9+7] = points_octo->array[1];
        triangles_octo->array[iAngle*9+8] = points_octo->array[2];         

        points_destroy(points_octo);

        return triangles_octo;

    }

    points_obj * space_points_triangles(const triangles_obj * triangles) {

        unsigned int iTriangle;
        unsigned int iPointInTriangle;
        unsigned int iPoint;
        unsigned int iPoint2;
        unsigned int nPoints;
    
        float diff, dist;        
        float point[3];

        float shortestDistance;
        float limitDistance;

        char * added;
        unsigned int iPointCompare;
        float distance;
        float dx, dy, dz;

        points_obj * pointsAll;
        points_obj * pointsContainer;
        points_obj * pointsUnique;

        // Copy all points from triangles in an array of points

        pointsAll = points_construct_zero(triangles->nTriangles*3);

        nPoints = 0;

        for (iTriangle = 0; iTriangle < triangles->nTriangles; iTriangle++) {

            for (iPointInTriangle = 0; iPointInTriangle < 3; iPointInTriangle++) {

                point[0] = triangles->array[iTriangle * 9 + iPointInTriangle * 3 + 0];
                point[1] = triangles->array[iTriangle * 9 + iPointInTriangle * 3 + 1];
                point[2] = triangles->array[iTriangle * 9 + iPointInTriangle * 3 + 2];                

                pointsAll->array[nPoints * 3 + 0] = point[0];
                pointsAll->array[nPoints * 3 + 1] = point[1];
                pointsAll->array[nPoints * 3 + 2] = point[2];
                nPoints++;

            }

        }

        // Shortest distance

        shortestDistance = space_distances_shortest_triangles(triangles);
        limitDistance = 0.5 * shortestDistance;

        // Remove duplicate

        added = (char *) malloc(pointsAll->nPoints * sizeof(char));
        memset((void *) added, 0x00, pointsAll->nPoints * sizeof(char));

        pointsContainer = points_construct_zero(pointsAll->nPoints);

        nPoints = 0;

        for (iPoint = 0; iPoint < pointsAll->nPoints; iPoint++) {

            if (added[iPoint] == 0x00) {

                for (iPoint2 = 0; iPoint2 < pointsAll->nPoints; iPoint2++) {

                    dx = pointsAll->array[iPoint*3+0] - pointsAll->array[iPoint2*3+0];
                    dy = pointsAll->array[iPoint*3+1] - pointsAll->array[iPoint2*3+1];
                    dz = pointsAll->array[iPoint*3+2] - pointsAll->array[iPoint2*3+2];

                    distance = dx * dx + dy * dy + dz * dz;

                    if (distance < (limitDistance*limitDistance)) {
                        
                        added[iPoint2] = 0x01;

                    }

                }

                added[iPoint] = 0x02;
                nPoints++;               

            }

        }

        // Load unique points

        pointsUnique = points_construct_zero(nPoints);
        nPoints = 0;

        for (iPoint = 0; iPoint < pointsContainer->nPoints; iPoint++) {

            if (added[iPoint] == 0x02) {

                pointsUnique->array[nPoints*3+0] = pointsAll->array[iPoint*3+0];
                pointsUnique->array[nPoints*3+1] = pointsAll->array[iPoint*3+1];
                pointsUnique->array[nPoints*3+2] = pointsAll->array[iPoint*3+2];

                nPoints++;

            }

        }

        points_destroy(pointsAll);
        points_destroy(pointsContainer);

        free((void *) added);

        return pointsUnique;

    }

    points_obj * space_points_fine(const points_obj * points, const unsigned int level) {

        points_obj * obj;
        
        unsigned int nPointsCoarse;
        unsigned int nPointsFine;
        unsigned int nFinesPerCoarse;
        unsigned int pow2, pow4;
        unsigned int iLevel;

        unsigned int iCoarse;
        triangles_obj * triangles1;
        triangles_obj * triangles2;
        points_obj * pointsFine;

        pow2 = 1;
        pow4 = 1;

        for (iLevel = 1; iLevel <= level; iLevel++) {

            pow2 *= 2;
            pow4 *= 4;

        }

        nFinesPerCoarse = (4 * (pow2 + pow4) + 1);

        nPointsCoarse = points->nPoints;
        nPointsFine = nPointsCoarse * nFinesPerCoarse;

        obj = points_construct_zero(nPointsFine);

        for (iCoarse = 0; iCoarse < nPointsCoarse; iCoarse++) {

            triangles1 = space_triangles_points(points, iCoarse);

            for (iLevel = 0; iLevel < level; iLevel++) {

                triangles2 = space_triangles_level_next(triangles1);
                triangles_destroy(triangles1);
                triangles1 = triangles2;

            }

            pointsFine = space_points_triangles(triangles1);
            triangles_destroy(triangles1);

            memcpy(&(obj->array[iCoarse*nFinesPerCoarse*3]), pointsFine->array, nFinesPerCoarse * 3 * sizeof(float));
            points_destroy(pointsFine);

        }

        return obj;

    }

    points_obj * space_sphere(const unsigned int level) {

        points_obj * obj;
        triangles_obj * triangles;

        triangles = space_triangles_level_level(level);
        obj = space_points_triangles(triangles);
        triangles_destroy(triangles);

        return obj;

    }

    points_obj * space_halfsphere(const unsigned int level) {

        points_obj * obj;

        triangles_obj * triangles;
        points_obj * pointsSphere;
        unsigned int nPoints;
        unsigned int iPoint;

        triangles = space_triangles_level_level(level);
        pointsSphere = space_points_triangles(triangles);

        nPoints = 0;

        for (iPoint = 0; iPoint < pointsSphere->nPoints; iPoint++) {
        
            if (pointsSphere->array[iPoint*3+2] >= 0.0f) {
            
                nPoints++;

            }

        }

        obj = points_construct_zero(nPoints);
        nPoints = 0;

        for (iPoint = 0; iPoint < pointsSphere->nPoints; iPoint++) {

            if (pointsSphere->array[iPoint*3+2] >= 0.0f) {
            
                obj->array[nPoints*3+0] = pointsSphere->array[iPoint*3+0];
                obj->array[nPoints*3+1] = pointsSphere->array[iPoint*3+1];
                obj->array[nPoints*3+2] = pointsSphere->array[iPoint*3+2];

                nPoints++;

            }

        }

        triangles_destroy(triangles);  
        points_destroy(pointsSphere);

        return obj;

    }

    float space_distances_shortest_triangles(const triangles_obj * triangles) {

        float shortestDistance;
        float x1, y1, z1;
        float x2, y2, z2;
        float x3, y3, z3;
        float dist12, dist23, dist31;
        unsigned int iTriangle;

        shortestDistance = +INFINITY;

        for (iTriangle = 0; iTriangle < triangles->nTriangles; iTriangle++) {

            x1 = triangles->array[iTriangle * 9 + 0];
            y1 = triangles->array[iTriangle * 9 + 1];
            z1 = triangles->array[iTriangle * 9 + 2];
            x2 = triangles->array[iTriangle * 9 + 3];
            y2 = triangles->array[iTriangle * 9 + 4];
            z2 = triangles->array[iTriangle * 9 + 5];
            x3 = triangles->array[iTriangle * 9 + 6];
            y3 = triangles->array[iTriangle * 9 + 7];
            z3 = triangles->array[iTriangle * 9 + 8];

            dist12 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
            dist23 = (x2-x3)*(x2-x3) + (y2-y3)*(y2-y3) + (z2-z3)*(z2-z3);
            dist31 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) + (z3-z1)*(z3-z1);

            if (dist12 < shortestDistance) {
                shortestDistance = dist12;
            }
            if (dist23 < shortestDistance) {
                shortestDistance = dist23;
            }
            if (dist31 < shortestDistance) {
                shortestDistance = dist31;
            }

        }

        shortestDistance = sqrtf(shortestDistance);

        return shortestDistance;        

    }

    float space_distances_shortest_points(const points_obj * points) {

        float shortestDistance;
        float x1, y1, z1;
        float x2, y2, z2;
        float dist;
        unsigned int iPoint;
        unsigned int iPoint2;

        shortestDistance = +INFINITY;       

        for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

            x1 = points->array[iPoint*3+0];
            y1 = points->array[iPoint*3+1];
            z1 = points->array[iPoint*3+2];

            for (iPoint2 = 0; iPoint2 < points->nPoints; iPoint2++) {

                if (iPoint != iPoint2) {

                    x2 = points->array[iPoint2*3+0];
                    y2 = points->array[iPoint2*3+1];
                    z2 = points->array[iPoint2*3+2];                

                    dist = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);

                    if (dist < shortestDistance) {

                        shortestDistance = dist;

                    }

                }

            }

        }

        shortestDistance = sqrtf(shortestDistance);

        return shortestDistance;

    }
