    
    #include "freq2freq.h"

    freq2freq_obj * freq2freq_construct_zero(const unsigned int halfFrameSize, const unsigned int lowPassCut, const float epsilon) {

        freq2freq_obj * obj;

        obj = (freq2freq_obj *) malloc(sizeof(freq2freq_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->lowPassCut = lowPassCut;
        obj->epsilon = epsilon;

        return obj;

    }

    void freq2freq_destroy(freq2freq_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_process_phasor(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors) {

        unsigned int iSignal, iSample;
        float real, imag;
        float magnitude;        

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            for (iSample = 0; iSample < freqs->halfFrameSize; iSample++) {

                real = freqs->array[iSignal][iSample * 2 + 0];
                imag = freqs->array[iSignal][iSample * 2 + 1];
                magnitude = sqrtf(real*real+imag*imag) + obj->epsilon;

                phasors->array[iSignal][iSample * 2 + 0] = real / magnitude;
                phasors->array[iSignal][iSample * 2 + 1] = imag / magnitude;

            }

        }

    }

    void freq2freq_process_product(freq2freq_obj * obj, const freqs_obj * freqs1, const freqs_obj * freqs2, const pairs_obj * pairs, freqs_obj * freqs12) {

        unsigned int iSignal1, iSignal2, iSignal12, iSample;
        float real1, imag1;
        float real2, imag2;

        iSignal12 = 0;

        for (iSignal1 = 0; iSignal1 < freqs1->nSignals; iSignal1++) {

            for (iSignal2 = (iSignal1+1); iSignal2 < freqs2->nSignals; iSignal2++) {

                if (pairs->array[iSignal12] == 0x01) {

                    for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                        real1 = freqs1->array[iSignal1][iSample * 2 + 0];
                        imag1 = freqs1->array[iSignal1][iSample * 2 + 1];
                        real2 = freqs2->array[iSignal2][iSample * 2 + 0];
                        imag2 = freqs2->array[iSignal2][iSample * 2 + 1];

                        freqs12->array[iSignal12][iSample * 2 + 0] = real1 * real2 + imag1 * imag2;
                        freqs12->array[iSignal12][iSample * 2 + 1] = imag1 * real2 - imag2 * real1;                    

                    }

                }

                iSignal12++;

            }

        }

    }

    void freq2freq_process_lowpass(freq2freq_obj * obj, const freqs_obj * freqsAllPass, freqs_obj * freqsLowPass) {

        unsigned int iSignal;

        freqs_zero(freqsLowPass);

        for (iSignal = 0; iSignal < freqsAllPass->nSignals; iSignal++) {

            memcpy(freqsLowPass->array[iSignal], freqsAllPass->array[iSignal], sizeof(float) * 2 * obj->lowPassCut);               

        }

    }

    void freq2freq_process_delaysum(freq2freq_obj * obj, const freqs_obj * freqsChannels, const shifts_obj * shifts, const gains_obj * gains, const masks_obj * masks, freqs_obj * freqsSeps) {

        unsigned int iSep;
        unsigned int iChannel;
        unsigned int iSample;

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int nSamples;
        float N;

        float channelReal;
        float channelImag;

        float gainTotal;        
        float gain;
        float tau;
        float phase;
        
        float shiftReal;
        float shiftImag;
        
        float sepReal;
        float sepImag;

        nSeps = freqsSeps->nSignals;
        nChannels = freqsChannels->nSignals;
        nSamples = freqsChannels->halfFrameSize;

        N = (float) (2 * (freqsChannels->halfFrameSize-1));

        for (iSep = 0; iSep < nSeps; iSep++) {

            memset(freqsSeps->array[iSep], 0x00, sizeof(float) * nSamples * 2);

            gainTotal = 0.0f;

            for (iChannel = 0; iChannel < nChannels; iChannel++) {

                if (masks->array[iSep * nChannels + iChannel] == 0x01) {

                    gainTotal += gains->array[iSep * nChannels + iChannel];

                }

            }

            for (iChannel = 0; iChannel < nChannels; iChannel++) {

                if (masks->array[iSep * nChannels + iChannel] == 0x01) {

                    gain = gains->array[iSep * nChannels + iChannel] / gainTotal;
                    tau = shifts->array[iSep * nChannels + iChannel];

                    for (iSample = 0; iSample < freqsChannels->halfFrameSize; iSample++) {

                        phase = 2.0f * M_PI * tau * ((float) iSample) / N;

                        shiftReal = gain * cosf(phase);
                        shiftImag = gain * sinf(phase);

                        channelReal = freqsChannels->array[iChannel][iSample * 2 + 0];
                        channelImag = freqsChannels->array[iChannel][iSample * 2 + 1];

                        sepReal = channelReal * shiftReal - channelImag * shiftImag;
                        sepImag = channelImag * shiftReal + channelReal * shiftImag;

                        freqsSeps->array[iSep][iSample * 2 + 0] += sepReal;
                        freqsSeps->array[iSep][iSample * 2 + 1] += sepImag;

                    }

                }

            }

        }

    }

    void freq2freq_process_postfilter(freq2freq_obj * obj, const freqs_obj * freqsChannels, const freqs_obj * freqsSeps, const gains_obj * gains, const masks_obj * masks, freqs_obj * freqsPosts) {

        unsigned int iSep;
        unsigned int iChannel;
        unsigned int iSample;

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int nSamples;        

        float sepReal;
        float sepImag;
        float sepPwr;

        float gain;
        float gainTotal;
        float gainTotal2;

        float channelReal;
        float channelImag;
        float channelPwr;
        float channelsPwr;

        float ratio;
        float factor;

        nSeps = freqsSeps->nSignals;
        nChannels = freqsChannels->nSignals;
        nSamples = freqsChannels->halfFrameSize;

        for (iSample = 0; iSample < nSamples; iSample++) {

            for (iSep = 0; iSep < nSeps; iSep++) {

                sepReal = freqsSeps->array[iSep][iSample * 2 + 0];
                sepImag = freqsSeps->array[iSep][iSample * 2 + 1];
                sepPwr = sepReal * sepReal + sepImag * sepImag;

                gainTotal = 0.0f;
                gainTotal2 = 0.0f;

                for (iChannel = 0; iChannel < nChannels; iChannel++) {

                    if (masks->array[iSep * nChannels + iChannel] == 0x01) {

                        gain = gains->array[iSep * nChannels + iChannel];
                        gainTotal += gain;
                        gainTotal2 += gain * gain;

                    }

                }

                channelsPwr = 0.0f;

                for (iChannel = 0; iChannel < nChannels; iChannel++) {

                    if (masks->array[iSep * nChannels + iChannel] == 0x01) {

                        gain = gains->array[iSep * nChannels + iChannel] / gainTotal;

                        channelReal = gain * freqsChannels->array[iChannel][iSample * 2 + 0];
                        channelImag = gain * freqsChannels->array[iChannel][iSample * 2 + 1];
                        channelPwr = channelReal * channelReal + channelImag * channelImag;

                        channelsPwr += channelPwr;

                    }

                }

                ratio = sepPwr / (channelsPwr * gainTotal2 + obj->epsilon);

                factor = 0.9f / (1.0f + expf(-20.0f * (ratio-0.5f))) + 0.1f;

                freqsPosts->array[iSep][iSample * 2 + 0] = factor * freqsSeps->array[iSep][iSample * 2 + 0];
                freqsPosts->array[iSep][iSample * 2 + 1] = factor * freqsSeps->array[iSep][iSample * 2 + 1];

            }

        }

    }