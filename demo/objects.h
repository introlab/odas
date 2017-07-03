#ifndef __DEMO_OBJECTS
#define __DEMO_OBJECTS

    #include "configs.h"

    #include <odas/odas.h>
    #include <stdlib.h>

    typedef struct objects {
      
        unsigned int nMessages;

        asrc_hops_obj * asrc_hops_raw_object;
        amsg_hops_obj * amsg_hops_raw_object;        
        unsigned int asnk_hops_raw_object_count;
        asnk_hops_obj ** asnk_hops_raw_objects;                
        acon_hops_obj * acon_hops_raw_object; 

        amod_mapping_obj * amod_mapping_object;
        amsg_hops_obj * amsg_hops_mapping_object;
        unsigned int asnk_hops_mapping_object_count;
        asnk_hops_obj ** asnk_hops_mapping_objects;
        acon_hops_obj * acon_hops_mapping_object;              

        amod_resample_obj * amod_resample_object;
        amsg_hops_obj * amsg_hops_resample_object;
        unsigned int asnk_hops_resample_object_count;
        asnk_hops_obj ** asnk_hops_resample_objects;
        acon_hops_obj * acon_hops_resample_object;

        amod_stft_obj * amod_stft_object;
        amsg_spectra_obj * amsg_spectra_stft_object;
        unsigned int asnk_spectra_stft_object_count;
        asnk_spectra_obj ** asnk_spectra_stft_objects;
        acon_spectra_obj * acon_spectra_stft_object;

        amod_ssl_obj * amod_ssl_object;
        amsg_pots_obj * amsg_pots_ssl_object;
        unsigned int asnk_pots_ssl_object_count;
        asnk_pots_obj ** asnk_pots_ssl_objects;
        acon_pots_obj * acon_pots_ssl_object;

        amod_sst_obj * amod_sst_object;
        amsg_tracks_obj * amsg_tracks_sst_object;
        unsigned int asnk_tracks_sst_object_count;
        asnk_tracks_obj ** asnk_tracks_sst_objects;
        acon_tracks_obj * acon_tracks_sst_object;

        amod_sss_obj * amod_sss_object;
        amsg_spectra_obj * amsg_spectra_sss_object;
        unsigned int asnk_spectra_sss_object_count;
        asnk_spectra_obj ** asnk_spectra_sss_objects;
        acon_spectra_obj * acon_spectra_sss_object;

        amod_sspf_obj * amod_sspf_object;
        amsg_spectra_obj * amsg_spectra_sspf_object;
        unsigned int asnk_spectra_sspf_object_count;
        asnk_spectra_obj ** asnk_spectra_sspf_objects;
        acon_spectra_obj * acon_spectra_sspf_object;

    } objects;

    objects * objects_construct(const configs * cfgs);

    void objects_destroy(objects * objs);

#endif