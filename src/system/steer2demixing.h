#ifndef __ODAS_SYSTEM_STEER2DEMIXING
#define __ODAS_SYSTEM_STEER2DEMIXING

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    #include "../signal/demixing.h"
    #include "../signal/freq.h"
    #include "../signal/mask.h"
    #include "../signal/steer.h"
    #include "../signal/track.h"

    #include "../utils/cmatrix.h"
    
    typedef struct steer2demixing_ds_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;
        float epsilon;

        float * gains2;

    } steer2demixing_ds_obj;

    typedef struct steer2demixing_gss_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        float mu;
        float lambda;

        cmatrix_obj * X;
        cmatrix_obj * XH;

        cmatrix_obj ** Y;
        cmatrix_obj ** YH;
        cmatrix_obj ** Ryy;
        cmatrix_obj ** E;
        cmatrix_obj ** A;
        cmatrix_obj ** AH;
        cmatrix_obj ** Wn;
        cmatrix_obj ** Wnp1;
        cmatrix_obj ** dJ1;
        cmatrix_obj ** dJ2;

    } steer2demixing_gss_obj;

    typedef struct steer2demixing_mvdr_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

        float sigma;

    } steer2demixing_mvdr_obj;


    steer2demixing_ds_obj * steer2demixing_ds_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float epsilon);

    void steer2demixing_ds_destroy(steer2demixing_ds_obj * obj);

    void steer2demixing_ds_process(steer2demixing_ds_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, demixings_obj * demixings);


    steer2demixing_gss_obj * steer2demixing_gss_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float mu, const float lambda);

    void steer2demixing_gss_destroy(steer2demixing_gss_obj * obj);

    void steer2demixing_gss_process(steer2demixing_gss_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, demixings_obj * demixings);

    
    steer2demixing_mvdr_obj * steer2demixing_mvdr_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float sigma);

    void steer2demixing_mvdr_process(steer2demixing_mvdr_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, demixings_obj * demixings);

    void steer2demixing_mvdr_destroy(steer2demixing_mvdr_obj * obj);

#endif