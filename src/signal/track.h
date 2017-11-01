#ifndef __ODAS_SIGNAL_TRACK
#define __ODAS_SIGNAL_TRACK
    
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct tracks_obj {

        unsigned int nTracks;
        unsigned long long * ids;
        float * array;
        float * activity;
        
    } tracks_obj;

    tracks_obj * tracks_construct_zero(const unsigned int nTracks);

    void tracks_destroy(tracks_obj * obj);

    tracks_obj * tracks_clone(const tracks_obj * obj);

    void tracks_copy(tracks_obj * dest, const tracks_obj * src);

    void tracks_zero(tracks_obj * obj);

    void tracks_printf(const tracks_obj * obj);

#endif