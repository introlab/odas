    
    #include "aimg.h"

    aimg_obj * aimg_construct_zero(const unsigned int aimgSize) {

        aimg_obj * obj;

        obj = (aimg_obj *) malloc(sizeof(aimg_obj));

        obj->aimgSize = aimgSize;
        obj->array = (float *) malloc(sizeof(float) * aimgSize);
        memset(obj->array, 0x00, aimgSize * sizeof(float));       

        return obj;

    }

    void aimg_destroy(aimg_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void aimg_printf(const aimg_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSample = 0; iSample < obj->aimgSize; iSample++) {

            printf("%+1.5f ",obj->array[iSample]);

            if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->aimgSize)) {
                printf("\n");
            }

        }

        printf("\n");

    }