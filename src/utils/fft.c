
    #include "fft.h"

    fft_obj * fft_construct(const unsigned int frameSize) {

        fft_obj * obj;

        obj = (fft_obj *) malloc(sizeof(fft_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2+1;
        obj->realArray = (float *) fftwf_malloc(sizeof(float) * obj->frameSize);
        obj->complexArray = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * obj->halfFrameSize);

        obj->R2C = fftwf_plan_dft_r2c_1d( obj->frameSize, obj->realArray, obj->complexArray, FFTW_ESTIMATE );
        obj->C2R = fftwf_plan_dft_c2r_1d( obj->frameSize, obj->complexArray, obj->realArray, FFTW_ESTIMATE );

        return obj;

    }

    void fft_destroy(fft_obj * obj) {

        fftwf_destroy_plan( obj->R2C );
        fftwf_destroy_plan( obj->C2R );

        fftwf_free(obj->realArray);
        fftwf_free(obj->complexArray);

        fftwf_cleanup();

        free((void *) obj);

    }

    void fft_r2c(fft_obj * obj, const float * in, float * out) {

        unsigned int iSample;

        for (iSample = 0; iSample < obj->frameSize; iSample++) {

            obj->realArray[iSample] = in[iSample];

        }

        fftwf_execute( obj->R2C );

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            out[iSample*2+0] = obj->complexArray[iSample][0];
            out[iSample*2+1] = obj->complexArray[iSample][1];

        }


    }

    void fft_c2r(fft_obj * obj, const float * in, float * out) {

        unsigned int iSample;

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            obj->complexArray[iSample][0] = in[iSample*2+0];
            obj->complexArray[iSample][1] = in[iSample*2+1];

        }

        fftwf_execute( obj->C2R );

        for (iSample = 0; iSample < obj->frameSize; iSample++) {

            out[iSample] = obj->realArray[iSample] / ((float) obj->frameSize);

        }

    }