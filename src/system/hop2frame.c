    
    #include "hop2frame.h"

    hop2frame_obj * hop2frame_construct_zero(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nSignals) {

        hop2frame_obj * obj;
        unsigned int iSignal;

        obj = (hop2frame_obj *) malloc(sizeof(hop2frame_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;
        obj->nSignals = nSignals;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * frameSize);
            memset(obj->array[iSignal], 0x00, sizeof(float) * frameSize);
        }

        return obj;

    }

    void hop2frame_destroy(hop2frame_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void hop2frame_process(hop2frame_obj * obj, const hops_obj * hops, frames_obj * frames) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < hops->nSignals; iSignal++) {

            memmove(&(obj->array[iSignal][0]),
                    &(obj->array[iSignal][obj->hopSize]),
                    sizeof(float) * (obj->frameSize-obj->hopSize));

            memcpy(&(obj->array[iSignal][(obj->frameSize-obj->hopSize)]),
                   &(hops->array[iSignal][0]),
                   sizeof(float) * obj->hopSize);

            memcpy(frames->array[iSignal],
                   obj->array[iSignal],
                   sizeof(float) * obj->frameSize);

        }        

    }