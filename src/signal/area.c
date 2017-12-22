    
    #include "area.h"

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
