    
    #include "freq2env.h"

    freq2env_obj * freq2env_construct_zero(const unsigned int halfFrameSize, const unsigned int nSignals) {

        freq2env_obj * obj;

        obj = (freq2env_obj *) malloc(sizeof(freq2env_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->nSignals = nSignals;

        return obj;

    }

    void freq2env_destroy(freq2env_obj * obj) {

        free((void *) obj);

    }

    void freq2env_process(freq2env_obj * obj, const freqs_obj * freqs, envs_obj * envs) {

        unsigned int iSignal;
        unsigned int iSample;

        float real;
        float imag;
        float env;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                real = freqs->array[iSignal][iSample * 2 + 0];
                imag = freqs->array[iSignal][iSample * 2 + 1];

                env = real * real + imag * imag;

                envs->array[iSignal][iSample] = sqrtf(env);

            }

        }

    }