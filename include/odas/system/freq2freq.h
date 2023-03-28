#ifndef __ODAS_SYSTEM_FREQ2FREQ
#define __ODAS_SYSTEM_FREQ2FREQ

   /**
    * \file     freq2freq.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */

    #include <stdlib.h>
    #include <math.h>

    #include <signal/freq.h>
    #include <signal/env.h>
    #include <signal/pair.h>
    #include <signal/track.h>
    
    typedef struct freq2freq_phasor_obj {

        unsigned int halfFrameSize;
        float epsilon;

    } freq2freq_phasor_obj;

    typedef struct freq2freq_weightedphasor_obj {

        unsigned int halfFrameSize;
        float epsilon;

    } freq2freq_weightedphasor_obj;

    typedef struct freq2freq_product_obj {

        unsigned int halfFrameSize;

    } freq2freq_product_obj;

    typedef struct freq2freq_lowpass_obj {

        unsigned int halfFrameSize;
        unsigned int lowPassCut;

    } freq2freq_lowpass_obj;

    typedef struct freq2freq_interpolate_obj {

        unsigned halfFrameSize;
        unsigned halfFrameSizeInterp;

    } freq2freq_interpolate_obj;

    typedef struct freq2freq_gain_obj {

        unsigned int halfFrameSize;

    } freq2freq_gain_obj;

    freq2freq_phasor_obj * freq2freq_phasor_construct_zero(const unsigned int halfFrameSize, const float epsilon);

    void freq2freq_phasor_destroy(freq2freq_phasor_obj * obj);

    void freq2freq_phasor_process(freq2freq_phasor_obj * obj, const freqs_obj * freqs, freqs_obj * phasors);

    freq2freq_weightedphasor_obj * freq2freq_weightedphasor_construct_zero(const unsigned int halfFrameSize, const float epsilon);

    void freq2freq_weightedphasor_destroy(freq2freq_weightedphasor_obj * obj);

    void freq2freq_weightedphasor_process(freq2freq_weightedphasor_obj * obj, const freqs_obj * freqs, const envs_obj * weights, freqs_obj * weightedphasors);

    freq2freq_product_obj * freq2freq_product_construct_zero(const unsigned int halfFrameSize);

    void freq2freq_product_destroy(freq2freq_product_obj * obj);

    void freq2freq_product_process(freq2freq_product_obj * obj, const freqs_obj * freqs1, const freqs_obj * freqs2, const pairs_obj * pairs, freqs_obj * freqs12);

    freq2freq_lowpass_obj * freq2freq_lowpass_construct_zero(const unsigned int halfFrameSize, const unsigned int lowPassCut);

    void  freq2freq_lowpass_destroy(freq2freq_lowpass_obj * obj);

    void freq2freq_lowpass_process(freq2freq_lowpass_obj * obj, const freqs_obj * freqsAllPass, freqs_obj * freqsLowPass);

    freq2freq_interpolate_obj * freq2freq_interpolate_construct_zero(const unsigned int halfFrameSize, const unsigned int halfFrameSizeInterp);

    void freq2freq_interpolate_destroy(freq2freq_interpolate_obj * obj);

    void freq2freq_interpolate_process(freq2freq_interpolate_obj * obj, const freqs_obj * freqs, const freqs_obj * freqsInterp);

    freq2freq_gain_obj * freq2freq_gain_construct_zero(const unsigned int halfFrameSize);

    void freq2freq_gain_destroy(freq2freq_gain_obj * obj);

    void freq2freq_gain_process(freq2freq_gain_obj * obj, const freqs_obj * freqsIn, const envs_obj * envsIn, freqs_obj * freqsOut);

#endif
