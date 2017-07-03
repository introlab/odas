    
    #include "triangle.h"

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