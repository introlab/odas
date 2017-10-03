#ifndef __DEMO_OBJECTS
#define __DEMO_OBJECTS

    #include "configs.h"

    #include <odas/odas.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct objects {

        src_hops_obj * src_hops_mics_object;
        msg_hops_obj * msg_hops_mics_raw_object;        
        snk_hops_obj * snk_hops_mics_raw_object;                
        con_hops_obj * con_hops_mics_raw_object; 

        mod_mapping_obj * mod_mapping_mics_object;
        msg_hops_obj * msg_hops_mics_map_object;
        snk_hops_obj * snk_hops_mics_map_object;
        con_hops_obj * con_hops_mics_map_object;              

        mod_resample_obj * mod_resample_mics_object;
        msg_hops_obj * msg_hops_mics_rs_object;
        snk_hops_obj * snk_hops_mics_rs_object;
        con_hops_obj * con_hops_mics_rs_object;

        mod_stft_obj * mod_stft_mics_object;
        msg_spectra_obj * msg_spectra_mics_object;
        snk_spectra_obj * snk_spectra_mics_object;
        con_spectra_obj * con_spectra_mics_object;

        mod_ssl_obj * mod_ssl_object;
        msg_pots_obj * msg_pots_ssl_object;
        snk_pots_obj * snk_pots_ssl_object;
        con_pots_obj * con_pots_ssl_object;

        mod_sst_obj * mod_sst_object;
        msg_tracks_obj * msg_tracks_sst_object;
        snk_tracks_obj * snk_tracks_sst_object;
        con_tracks_obj * con_tracks_sst_object;

    } objects;   

    typedef struct aobjects {
      
        unsigned int nMessages;

        asrc_hops_obj * asrc_hops_mics_object;
        amsg_hops_obj * amsg_hops_mics_raw_object;
        asnk_hops_obj * asnk_hops_mics_raw_object;
        acon_hops_obj * acon_hops_mics_raw_object; 

        amod_mapping_obj * amod_mapping_mics_object;
        amsg_hops_obj * amsg_hops_mics_map_object;
        asnk_hops_obj * asnk_hops_mics_map_objects;
        acon_hops_obj * acon_hops_mics_map_object;              

        amod_resample_obj * amod_resample_mics_object;
        amsg_hops_obj * amsg_hops_mics_rs_object;
        asnk_hops_obj * asnk_hops_mics_rs_object;
        acon_hops_obj * acon_hops_mics_rs_object;

        amod_stft_obj * amod_stft_mics_object;
        amsg_spectra_obj * amsg_spectra_mics_object;
        asnk_spectra_obj * asnk_spectra_mics_object;
        acon_spectra_obj * acon_spectra_mics_object;

        amod_ssl_obj * amod_ssl_object;
        amsg_pots_obj * amsg_pots_ssl_object;
        asnk_pots_obj * asnk_pots_ssl_object;
        acon_pots_obj * acon_pots_ssl_object;

        amod_sst_obj * amod_sst_object;
        amsg_tracks_obj * amsg_tracks_sst_object;
        asnk_tracks_obj * asnk_tracks_sst_object;
        acon_tracks_obj * acon_tracks_sst_object;

    } aobjects;
 
    objects * objects_construct(const configs * cfgs);

    void objects_destroy(objects * objs);

    aobjects * aobjects_construct(const configs * cfgs);

    void aobjects_destroy(aobjects * objs);

#endif