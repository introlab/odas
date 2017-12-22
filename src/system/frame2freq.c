
    #include "frame2freq.h"

    frame2freq_obj * frame2freq_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        frame2freq_obj * obj;

        obj = (frame2freq_obj *) malloc(sizeof(frame2freq_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->win = windowing_roothann(frameSize);
        obj->frame = (float *) malloc(sizeof(float) * frameSize);
        memset(obj->frame, 0x00, sizeof(float) * frameSize);
        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void frame2freq_destroy(frame2freq_obj * obj) {

        window_destroy(obj->win);
        free((void *) obj->frame);
        fft_destroy(obj->fft);

        free((void *) obj);

    }

    void frame2freq_process(frame2freq_obj * obj, const frames_obj * frames, freqs_obj * freqs) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < frames->nSignals; iSignal++) {

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                obj->frame[iSample] = obj->win->array[iSample] * frames->array[iSignal][iSample];

            }

            fft_r2c(obj->fft, 
                    obj->frame,
                    freqs->array[iSignal]);

        }

    }