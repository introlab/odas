    
    #include "freq2acorr.h"

    freq2acorr_obj * freq2acorr_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        freq2acorr_obj * obj;

        obj = (freq2acorr_obj *) malloc(sizeof(freq2acorr_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        obj->frameSize = (halfFrameSize-1)*2;

        obj->arrayIn = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2);
        obj->arrayOut = (float *) malloc(sizeof(float) * obj->frameSize);

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void freq2acorr_destroy(freq2acorr_obj * obj) {

        free((void *) obj->arrayIn);
        free((void *) obj->arrayOut);
        fft_destroy(obj->fft);
        free((void *) obj);

    }

    void freq2acorr_process(freq2acorr_obj * obj, const freqs_obj * freqs, acorrs_obj * acorrs) {

        unsigned int iSignal;
        unsigned int iBin;

        float Yreal;
        float Yimag;
        float Ypwr;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            memset(obj->arrayIn, 0x00, sizeof(float) * obj->halfFrameSize * 2);

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                Yreal = freqs->array[iSignal][iBin * 2 + 0];
                Yimag = freqs->array[iSignal][iBin * 2 + 1];
                Ypwr = Yreal * Yreal + Yimag * Yimag;

                obj->arrayIn[iBin * 2 + 0] = Ypwr;
                obj->arrayIn[iBin * 2 + 1] = 0.0f;

            }

            fft_c2r(obj->fft, obj->arrayIn, obj->arrayOut);

            memcpy(acorrs->array[iSignal], obj->arrayOut, sizeof(float) * obj->halfFrameSize);

        }

    }