    
    #include "shift2freq.h"

    shift2freq_obj * shift2freq_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize) {

        shift2freq_obj * obj;
        unsigned int iSample;

        obj = (shift2freq_obj *) malloc(sizeof(shift2freq_obj));

        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->array = (float *) malloc(sizeof(float) * halfFrameSize);

        for (iSample = 0; iSample < halfFrameSize; iSample++) {

            obj->array[iSample] = 2.0f * M_PI * ((float) iSample) / ((float) ((halfFrameSize-1)*2));

        }

        return obj;

    }

    void shift2freq_destroy(shift2freq_obj * obj) {

        free((void *) obj);

    }

    void shift2freq_process(shift2freq_obj * obj, const shifts_obj * shifts, const gains_obj * gains, const masks_obj * masks, freqs_obj * freqs) {

        unsigned int iChannel;
        unsigned int iSample;
        float gainTotal;
        float normalize;

        gainTotal = 0.0f;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (masks->array[iChannel] == 0x01) {

                gainTotal += gains->array[iChannel];

            }

        }

        normalize = 1.0f / (gainTotal);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            if (masks->array[iChannel] == 0x01) {

                for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                    freqs->array[iChannel][iSample*2+0] = normalize * gains->array[iChannel] * cosf(obj->array[iSample] * shifts->array[iChannel]);
                    freqs->array[iChannel][iSample*2+1] = normalize * gains->array[iChannel] * sinf(obj->array[iSample] * shifts->array[iChannel]);

                }

            }

        }

    }