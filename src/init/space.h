#ifndef __ODAS_INIT_SPACE
#define __ODAS_INIT_SPACE

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