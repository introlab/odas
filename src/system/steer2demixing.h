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
        float epsilon;

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

        cmatrix_obj ** dJ1_EY;
        cmatrix_obj ** dJ1_4EY;
        cmatrix_obj ** dJ1_4EYXH;

        cmatrix_obj ** dJ2_WA;
        cmatrix_obj ** dJ2_WAmI;
        cmatrix_obj ** dJ2_2WAmI;
        cmatrix_obj ** dJ2_2WAmIAH;

        cmatrix_obj ** alpha_dJ1;
        cmatrix_obj ** alpha_dJ1_p_dJ2;
        cmatrix_obj ** mu_alpha_dJ1_p_dJ2;
        cmatrix_obj ** one_m_lambda_mu_Wn;
        cmatrix_obj ** one_m_lambda_mu_Wn_m_mu_alpha_dJ1_p_dJ2;

    } steer2demixing_gss_obj;

    typedef struct steer2demixing_mvdr_obj {

    } steer2demixing_mvdr_obj;


    steer2demixing_ds_obj * steer2demixing_ds_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float epsilon);

    void steer2demixing_ds_destroy(steer2demixing_ds_obj * obj);

    void steer2demixing_ds_process(steer2demixing_ds_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, demixings_obj * demixings);


    steer2demixing_gss_obj * steer2demixing_gss_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float mu, const float lambda, const float epsilon);

    void steer2demixing_gss_destroy(steer2demixing_gss_obj * obj);

    void steer2demixing_gss_process(steer2demixing_gss_obj * obj, const tracks_obj * tracksPrev, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, const demixings_obj * demixingsPrev, demixings_obj * demixings);

    
    steer2demixing_mvdr_obj * steer2demixing_mvdr_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize, const float alpha, const float sigma, const unsigned int deltaK);

    void steer2demixing_mvdr_destroy(steer2demixing_mvdr_obj * obj);

    void steer2demixing_mvdr_process(steer2demixing_mvdr_obj * obj, const tracks_obj * tracks, const steers_obj * steers, const masks_obj * masks, const freqs_obj * freqs, demixings_obj * demixings);
    

#endif