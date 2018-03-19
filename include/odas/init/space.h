#ifndef __ODAS_INIT_SPACE
#define __ODAS_INIT_SPACE

   /**
    * \file     space.h
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

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../signal/triangle.h"
    #include "../signal/point.h"

    triangles_obj * space_triangles_level_zero(void);

    triangles_obj * space_triangles_level_next(const triangles_obj * triangles);

    triangles_obj * space_triangles_level_level(const unsigned int level);    

    triangles_obj * space_triangles_points(const points_obj * points, const unsigned int index);

    points_obj * space_points_triangles(const triangles_obj * triangles);

    points_obj * space_points_fine(const points_obj * points, const unsigned int level);

    points_obj * space_sphere(const unsigned int level);

    points_obj * space_halfsphere(const unsigned int level);

    float space_distances_shortest_triangles(const triangles_obj * triangles);

    float space_distances_shortest_points(const points_obj * points);    

#endif