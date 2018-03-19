#ifndef __ODAS_SYSTEM_FREQ2FREQ
#define __ODAS_SYSTEM_FREQ2FREQ

   /**
    * \file     freq2freq.h
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
