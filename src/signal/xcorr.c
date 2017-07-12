    
    #include "xcorr.h"

    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        xcorrs_obj * obj;
        unsigned int iSignal;

        obj = (xcorrs_obj *) malloc(sizeof(xcorrs_obj));

        obj->nSignals = nSignals;
        obj->frameSize = frameSize;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);
        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * frameSize);
            memset(obj->array[iSignal], 0x00, frameSize * sizeof(float));    
        }
        
        return obj;

    }

    void xcorrs_destroy(xcorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }
        free((void *) obj->array);

        free((void *) obj);

    }

    void xcorrs_copy(xcorrs_obj * dest, const xcorrs_obj * src) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < src->nSignals; iSignal++) {
            memcpy(dest->array[iSignal], src->array[iSignal], src->frameSize * sizeof(float));
        }

    }

    void xcorrs_zero(xcorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            memset(obj->array[iSignal], 0x00, obj->frameSize * sizeof(float));
        }

    }

    void xcorrs_printf(const xcorrs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal][iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->frameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }

    void xcorrs_printf_signal(const xcorrs_obj * obj, const unsigned int iSignal) {

        unsigned int iSample;

        printf("(%04u): ",iSignal);

        for (iSample = 0; iSample < obj->frameSize; iSample++) {

            printf("%+1.5f ",obj->array[iSignal][iSample]);

            if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->frameSize)) {
                printf("\n        ");
            }

        }

        printf("\n");

    }