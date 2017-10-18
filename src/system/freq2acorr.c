    
    #include "freq2acorr.h"

    freq2acorr_obj * freq2acorr_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        freq2acorr_obj * obj;

        obj = (freq2acorr_obj *) malloc(sizeof(freq2acorr_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        obj->frameSize = (halfFrameSize-1)*2;

        obj->array = (float *) malloc(sizeof(float) * obj->frameSize);

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void freq2acorr_destroy(freq2acorr_obj * obj) {

        free((void *) obj->array);
        fft_destroy(obj->fft);
        free((void *) obj);

    }

    void freq2acorr_process(freq2acorr_obj * obj, const freqs_obj * freqs, acorrs_obj * acorrs) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            fft_c2r(obj->fft, freqs->array[iSignal], obj->array);

            memcpy(acorrs->array[iSignal], obj->array, sizeof(float) * obj->halfFrameSize);

        }

    }