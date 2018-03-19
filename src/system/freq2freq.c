
   /**
    * \file     freq2freq.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <system/freq2freq.h>

    freq2freq_phasor_obj * freq2freq_phasor_construct_zero(const unsigned int halfFrameSize, const float epsilon) {

        freq2freq_phasor_obj * obj;

        obj = (freq2freq_phasor_obj *) malloc(sizeof(freq2freq_phasor_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->epsilon = epsilon;

        return obj;

    }

    void freq2freq_phasor_destroy(freq2freq_phasor_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_phasor_process(freq2freq_phasor_obj * obj, const freqs_obj * freqs, freqs_obj * phasors) {

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

    freq2freq_weightedphasor_obj * freq2freq_weightedphasor_construct_zero(const unsigned int halfFrameSize, const float epsilon) {

        freq2freq_weightedphasor_obj * obj;

        obj = (freq2freq_weightedphasor_obj *) malloc(sizeof(freq2freq_weightedphasor_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->epsilon = epsilon;

        return obj;        

    }

    void freq2freq_weightedphasor_destroy(freq2freq_weightedphasor_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_weightedphasor_process(freq2freq_weightedphasor_obj * obj, const freqs_obj * freqs, const envs_obj * weights, freqs_obj * weightedphasors) {

        unsigned int iSignal, iSample;
        float real, imag;
        float magnitude;        
        float weight;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            for (iSample = 0; iSample < freqs->halfFrameSize; iSample++) {

                real = freqs->array[iSignal][iSample * 2 + 0];
                imag = freqs->array[iSignal][iSample * 2 + 1];
                magnitude = sqrtf(real*real+imag*imag) + obj->epsilon;
                weight = weights->array[iSignal][iSample];

                weightedphasors->array[iSignal][iSample * 2 + 0] = weight * real / magnitude;
                weightedphasors->array[iSignal][iSample * 2 + 1] = weight * imag / magnitude;

            }

        }          

    }

    freq2freq_product_obj * freq2freq_product_construct_zero(const unsigned int halfFrameSize) {

        freq2freq_product_obj * obj;

        obj = (freq2freq_product_obj *) malloc(sizeof(freq2freq_product_obj));

        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void freq2freq_product_destroy(freq2freq_product_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_product_process(freq2freq_product_obj * obj, const freqs_obj * freqs1, const freqs_obj * freqs2, const pairs_obj * pairs, freqs_obj * freqs12) {

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

    freq2freq_lowpass_obj * freq2freq_lowpass_construct_zero(const unsigned int halfFrameSize, const unsigned int lowPassCut) {

        freq2freq_lowpass_obj * obj;

        obj = (freq2freq_lowpass_obj *) malloc(sizeof(freq2freq_lowpass_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->lowPassCut = lowPassCut;

        return obj;

    }

    void  freq2freq_lowpass_destroy(freq2freq_lowpass_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_lowpass_process(freq2freq_lowpass_obj * obj, const freqs_obj * freqsAllPass, freqs_obj * freqsLowPass) {

        unsigned int iSignal;

        freqs_zero(freqsLowPass);

        for (iSignal = 0; iSignal < freqsAllPass->nSignals; iSignal++) {

            memcpy(freqsLowPass->array[iSignal], freqsAllPass->array[iSignal], sizeof(float) * 2 * obj->lowPassCut);               

        }        

    }

    freq2freq_interpolate_obj * freq2freq_interpolate_construct_zero(const unsigned int halfFrameSize, const unsigned int halfFrameSizeInterp) {

        freq2freq_interpolate_obj * obj;

        obj = (freq2freq_interpolate_obj *) malloc(sizeof(freq2freq_interpolate_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->halfFrameSizeInterp = halfFrameSizeInterp;

        return obj;

    }

    void freq2freq_interpolate_destroy(freq2freq_interpolate_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_interpolate_process(freq2freq_interpolate_obj * obj, const freqs_obj * freqs, const freqs_obj * freqsInterp) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            memset(freqsInterp->array[iSignal], 0x00, sizeof(float) * 2 * obj->halfFrameSizeInterp);
            memcpy(freqsInterp->array[iSignal], freqs->array[iSignal], sizeof(float) * 2 * obj->halfFrameSize);

        }        

    }

    freq2freq_gain_obj * freq2freq_gain_construct_zero(const unsigned int halfFrameSize) {

        freq2freq_gain_obj * obj;

        obj = (freq2freq_gain_obj *) malloc(sizeof(freq2freq_gain_obj));

        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void freq2freq_gain_destroy(freq2freq_gain_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_gain_process(freq2freq_gain_obj * obj, const freqs_obj * freqsIn, const envs_obj * envsIn, freqs_obj * freqsOut) {

        unsigned int iSignal;
        unsigned int iSample;

        float xReal;
        float xImag;
        float g;
        float yReal;
        float yImag;

        for (iSignal = 0; iSignal < freqsIn->nSignals; iSignal++) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                xReal = freqsIn->array[iSignal][iSample*2+0];
                xImag = freqsIn->array[iSignal][iSample*2+1];
                g = envsIn->array[iSignal][iSample];

                yReal = g * xReal;
                yImag = g * xImag;

                freqsOut->array[iSignal][iSample*2+0] = yReal;
                freqsOut->array[iSignal][iSample*2+1] = yImag;

            }

        }

    }
