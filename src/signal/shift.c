    
    #include "shift.h"

    shifts_obj * shifts_construct_zero(const unsigned int nSeps, const unsigned int nChannels) {

        shifts_obj * obj;
        unsigned int iChannel;

        obj = (shifts_obj *) malloc(sizeof(shifts_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;

        obj->array = (float *) malloc(sizeof(float) * nSeps * nChannels);
        memset(obj->array, 0x00, sizeof(float) * nSeps * nChannels);

        return obj;

    }

    void shifts_destroy(shifts_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void shifts_printf(const shifts_obj * obj) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("(%02u): ",iSep);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%+1.3f ",obj->array[iChannel]);

            }

            printf("\n");

        }

    }