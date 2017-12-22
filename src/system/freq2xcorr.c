    
    #include "freq2xcorr.h"

    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        freq2xcorr_obj * obj;

        obj = (freq2xcorr_obj *) malloc(sizeof(freq2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->frame = (float *) malloc(sizeof(float) * halfFrameSize * 2);
        memset(obj->frame,0x00,sizeof(float)* halfFrameSize * 2);

        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void freq2xcorr_destroy(freq2xcorr_obj * obj) {

        fft_destroy(obj->fft);
        free((void *) obj->frame);

        free((void *) obj);

    }

        void freq2xcorr_process(freq2xcorr_obj * obj, const freqs_obj * freqs, const pairs_obj * pairs, xcorrs_obj * xcorrs) {

        unsigned int iSignal;
        unsigned int iSample;
        unsigned int iSampleSrc;
        unsigned int iSampleDest;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            if (pairs->array[iSignal] == 0x01) {

                fft_c2r(obj->fft, 
                        freqs->array[iSignal],
                        obj->frame);

                memcpy(&(xcorrs->array[iSignal][0]),&(obj->frame[obj->frameSize/2]),(obj->frameSize/2)*sizeof(float));
                memcpy(&(xcorrs->array[iSignal][obj->frameSize/2]),&(obj->frame[0]),(obj->frameSize/2)*sizeof(float));

            }

        }

    }