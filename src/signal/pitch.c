    
    #include "pitch.h"

    pitches_obj * pitches_construct_zero(const unsigned int nSignals) {

        pitches_obj * obj;

        obj = (pitches_obj *) malloc(sizeof(pitches_obj));

        obj->nSignals = nSignals;
        obj->array = (float *) malloc(sizeof(float) * nSignals);
        memset(obj->array, 0x00, sizeof(float) * nSignals);

        return obj;

    }

    void pitches_destroy(pitches_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pitches_copy(pitches_obj * dest, const pitches_obj * src) {

        memcpy(dest->array, src->array, sizeof(float) * src->nSignals);

    }

    void pitches_zero(pitches_obj * obj) {

        memset(obj->array, 0x00, sizeof(float) * obj->nSignals);

    }

    void pitches_printf(const pitches_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %1.5f\n",iSignal,obj->array[iSignal]);

        }

    }