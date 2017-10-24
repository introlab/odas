    
    #include "freq2env.h"

    freq2env_obj * freq2env_construct_zero(const unsigned int halfFrameSize) {

        freq2env_obj * obj;

        obj = (freq2env_obj *) malloc(sizeof(freq2env_obj));

        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void freq2env_destroy(freq2env_obj * obj) {

        free((void *) obj);

    }

    void freq2env_process(freq2env_obj * obj, const freqs_obj * freqs, envs_obj * envs) {

        unsigned int iSignal;
        unsigned int iBin;

        float Xreal;
        float Ximag;
        float X2;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                Xreal = freqs->array[iSignal][iBin * 2 + 0];
                Ximag = freqs->array[iSignal][iBin * 2 + 1];

                X2 = Xreal * Xreal + Ximag * Ximag;

                envs->array[iSignal][iBin] = X2;

            }

        }

    }