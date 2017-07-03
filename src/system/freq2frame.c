    
    #include "freq2frame.h"

    freq2frame_obj * freq2frame_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        freq2frame_obj * obj;

        obj = (freq2frame_obj *) malloc(sizeof(freq2frame_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->win = windowing_roothann(frameSize);
        obj->frame = (float *) malloc(sizeof(float) * frameSize);
        memset(obj->frame, 0x00, sizeof(float) * frameSize);
        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void freq2frame_destroy(freq2frame_obj * obj) {

        window_destroy(obj->win);
        free((void *) obj->frame);
        fft_destroy(obj->fft);

        free((void *) obj);        

    }

    void freq2frame_process(freq2frame_obj * obj, const freqs_obj * freqs, frames_obj * frames) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < frames->nSignals; iSignal++) {

            fft_c2r(obj->fft, 
                    freqs->array[iSignal],
                    obj->frame);

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                frames->array[iSignal][iSample] = obj->win->array[iSample] * obj->frame[iSample];

            }

        }

    }