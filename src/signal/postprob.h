#ifndef __ODAS_SIGNAL_POSTPROB
#define __ODAS_SIGNAL_POSTPROB

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct postprobs_obj {

        unsigned int nTracks;
        unsigned int nPots;

        float * arrayNew;
        float * arrayTrack;
        float * arrayTrackTotal;

    } postprobs_obj;    

    postprobs_obj * postprobs_construct_zero(const unsigned int nPots, const unsigned int nTracks);    

    void postprobs_destroy(postprobs_obj * obj);

    void postprobs_printf(const postprobs_obj * obj);

#endif