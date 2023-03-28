#ifndef __ODAS_SYSTEM_ENV2ENV
#define __ODAS_SYSTEM_ENV2ENV

   /**
    * \file     env2env.h
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
    #include <string.h>
    #include <math.h>

    #include <signal/env.h>
    #include <signal/track.h>
    #include <utils/fft.h>
    #include <utils/transcendental.h>

    typedef struct env2env_mcra_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        unsigned int bSize;
        float alphaS;
        unsigned int L;
        float delta;
        float alphaD;

        unsigned long long * idsPrev;
        unsigned int * l;

        float * b;
        float ** S;
        float ** Smin;
        float ** SminPrev;
        float ** SPrev;
        float ** Stmp;
        float ** StmpPrev;
        float ** Sf;
        float ** lambdaD;
        float ** lambdaDnext;

    } env2env_mcra_obj;

    typedef struct env2env_weight_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        float alphaD;
        float epsilon;

        float ** XPrev;
        float ** xi;
        float ** zetaPrev;

    } env2env_weight_obj;

    typedef struct env2env_interf_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        float eta;
        float alphaZ;

        float ** Zs;
        float ** ZsPrev;

    } env2env_interf_obj;

    typedef struct env2env_gainspeech_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        float alphaPmin;
        float epsilon;

        float ** gamma;
        float ** alphaP;
        float ** xi;
        float ** GH1;
        float ** v;

        transcendental_obj * transcendental;

    } env2env_gainspeech_obj;

    typedef struct env2env_probspeech_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;
        unsigned int frameSize;

        float theta;
        float alpha;
        float maxAbsenceProb;
        float Gmin;

        unsigned int winSizeLocal;
        unsigned int winSizeGlobal;
        unsigned int winSizeFrame;       

        fft_obj * fft;

        float * winLocal;
        float * winGlobal;
        float * winFrame;

        float * winLocalShifted;
        float * winGlobalShifted;
        float * winFrameShifted;

        float * winLocalShiftedFreq;
        float * winGlobalShiftedFreq;
        float * winFrameShiftedFreq;

        float ** xiTime;
        float ** xiFreq;

        float ** xiSmoothedLocalFreq;
        float ** xiSmoothedGlobalFreq;
        float ** xiSmoothedFrameFreq;
        float ** xiSmoothedLocalTime;
        float ** xiSmoothedGlobalTime;
        float ** xiSmoothedFrameTime;
        float ** xiSmoothedLocal;
        float ** xiSmoothedGlobal;
        float ** xiSmoothedFrame;

        float ** zetaLocal;
        float ** zetaLocalPrev;
        float ** zetaGlobal;
        float ** zetaGlobalPrev;
        float ** zetaFrame;
        float ** zetaFramePrev;

        float ** PLocal;
        float ** PGlobal;
        float ** PFrame;

        float ** q;
        float ** p;

    } env2env_probspeech_obj;

    typedef struct env2env_gainall_obj {

        unsigned int nChannels;
        unsigned int halfFrameSize;

        float Gmin;

    } env2env_gainall_obj;

    typedef struct env2env_gainratio_obj {

        unsigned int nInitChannels;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        float Gmin;
        float Gmid;
        float Gslope;

        float epsilon;

    } env2env_gainratio_obj;

    env2env_mcra_obj * env2env_mcra_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const unsigned int bSize, const float alphaS, const unsigned int L, const float delta, const float alphaD);

    void env2env_mcra_destroy(env2env_mcra_obj * obj);

    void env2env_mcra_process(env2env_mcra_obj * obj, const tracks_obj * tracks, const envs_obj * noisys, const envs_obj * estNoises, envs_obj * noises);

    env2env_weight_obj * env2env_weight_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float alphaD, const float epsilon);

    void env2env_weight_destroy(env2env_weight_obj * obj);

    void env2env_weight_process(env2env_weight_obj * obj, const tracks_obj * tracks, const envs_obj * noisys, const envs_obj * noises, envs_obj * weights);

    env2env_interf_obj * env2env_interf_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float eta, const float alphaZ);

    void env2env_interf_destroy(env2env_interf_obj * obj);

    void env2env_interf_process(env2env_interf_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * noises, envs_obj * interfs);

    env2env_gainspeech_obj * env2env_gainspeech_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float alphaPmin, const float epsilon);

    void env2env_gainspeech_destroy(env2env_gainspeech_obj * obj);

    void env2env_gainspeech_process(env2env_gainspeech_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * noises, envs_obj * gains, envs_obj * snrs, envs_obj * vs);

    env2env_probspeech_obj * env2env_probspeech_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float theta, const float alpha, const float maxAbsenceProb, const float Gmin, const unsigned int winSizeLocal, const unsigned int winSizeGlobal, const unsigned int winSizeFrame);

    void env2env_probspeech_destroy(env2env_probspeech_obj * obj);

    void env2env_probspeech_process(env2env_probspeech_obj * obj, const tracks_obj * tracks, const envs_obj * snrs, const envs_obj * vs, envs_obj * probspeechs);

    env2env_gainall_obj * env2env_gainall_construct_zero(const unsigned int nChannels, const unsigned int halfFrameSize, const float Gmin);

    void env2env_gainall_destroy(env2env_gainall_obj * obj);

    void env2env_gainall_process(env2env_gainall_obj * obj, const tracks_obj * tracks, const envs_obj * gainspeeches, const envs_obj * probspeeches, envs_obj * gainalls);

    env2env_gainratio_obj * env2env_gainratio_construct_zero(const unsigned int nInitChannels, const unsigned int nChannels, const unsigned int halfFrameSize, const float Gmin, const float Gmid, const float Gslope, const float epsilon);

    void env2env_gainratio_destroy(env2env_gainratio_obj * obj);

    void env2env_gainratio_process(env2env_gainratio_obj * obj, const tracks_obj * tracks, const envs_obj * seps, const envs_obj * diffuse, envs_obj * gainratio);

#endif
