#ifndef __ODASSERVERBF_OBJECTS
#define __ODASSERVERBF_OBJECTS

    #include <odas/odas.h>
    #include <stdlib.h>

    #include "configs.h"

    typedef struct objects {

        unsigned long long timeStamp;

        char * in1;
        char * in2;

        dsr_hops_obj * dsr_hops_in_object;
        dsr_targets_obj * dsr_targets_in_object;

        con_hops_obj * con_hops_in_object;
        mod_stft_obj * mod_stft_in_object;
        con_spectra_obj * con_spectra_in_object;
        con_targets_obj * con_targets_in_object;

        mod_tt_obj * mod_tt_object;
        mod_bf_obj * mod_bf_object;
        
        con_tracks_obj * con_tracks_out_object;
        con_spectra_obj * con_spectra_out_object;
        mod_istft_obj * mod_istft_out_object;
        con_hops_obj * con_hops_out_object;

        ser_hops_obj * ser_hops_out_object;
        ser_tracks_obj * ser_tracks_out_object;

        char * out1;
        char * out2;

    } objects;

    objects * objects_construct(const configs * cfgs);

    void objects_destroy(objects * objs);

    void objects_link(objects * objs);

    void objects_process(objects * objs);

#endif