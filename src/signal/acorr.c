
    #include "acorr.h"

    acorrs_obj * acorrs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        acorrs_obj * obj;
        unsigned int iSignal;

        obj = (acorrs_obj *) malloc(sizeof(acorrs_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {

            obj->array[iSignal] = (float *) malloc(sizeof(float) * halfFrameSize);

        }


        return obj;

    }

    void acorrs_destroy(acorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            free((void *) obj->array[iSignal]);

        }

        free((void *) obj->array);

        free((void *) obj);

    }

    void acorrs_copy(acorrs_obj * dest, const acorrs_obj * src) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {

            memcpy(dest->array[iSignal],src->array[iSignal], sizeof(float) * src->halfFrameSize);

        }

    }

    void acorrs_zero(acorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            memset(obj->array[iSignal], 0x00, sizeof(float) * obj->halfFrameSize);

        }

    }

    void acorrs_printf(const acorrs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal][iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->halfFrameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }
