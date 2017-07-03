    
    #include "point.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    points_obj * points_construct_zero(const unsigned int nPoints) {

        points_obj * obj;

        obj = (points_obj *) malloc(sizeof(points_obj));

        obj->nPoints = nPoints;
        obj->array = (float *) malloc(sizeof(float) * nPoints * 3);
        memset(obj->array, 0x00, nPoints * 3 * sizeof(float));

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    points_obj * points_clone(const points_obj * obj) {

        points_obj * clone;

        clone = (points_obj *) malloc(sizeof(points_obj));

        clone->nPoints = obj->nPoints;
        clone->array = (float *) malloc(sizeof(float) * obj->nPoints * 3);
        memcpy(clone->array, obj->array, obj->nPoints * 3 * sizeof(float));

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void points_destroy(points_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

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