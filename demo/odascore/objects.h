#ifndef __DEMO_OBJECTS
#define __DEMO_OBJECTS

    #include "configs.h"

    #include <odas/odas.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct objects {

        src_hops_obj * src_hops_mics_object;
        con_hops_obj * con_hops_mics_raw_object; 

        mod_mapping_obj * mod_mapping_mics_object;
        con_hops_obj * con_hops_mics_map_object;              

        mod_resample_obj * mod_resample_mics_object;
        con_hops_obj * con_hops_mics_rs_object;

        mod_stft_obj * mod_stft_mics_object;
        con_spectra_obj * con_spectra_mics_object;

        mod_noise_obj * mod_noise_mics_object;
        con_powers_obj * con_powers_mics_object;

        mod_ssl_obj * mod_ssl_object;
        snk_pots_obj * snk_pots_ssl_object;
        con_pots_obj * con_pots_ssl_object;

        inj_targets_obj * inj_targets_sst_object;
        con_targets_obj * con_targets_sst_object;

        mod_sst_obj * mod_sst_object;
        snk_tracks_obj * snk_tracks_sst_object;
        con_tracks_obj * con_tracks_sst_object;

        mod_sss_obj * mod_sss_object;
        con_spectra_obj * con_spectra_seps_object;
        con_spectra_obj * con_spectra_pfs_object;

        mod_istft_obj * mod_istft_seps_object;
        mod_istft_obj * mod_istft_pfs_object;
        con_hops_obj * con_hops_seps_object;
        con_hops_obj * con_hops_pfs_object;

        mod_resample_obj * mod_resample_seps_object;
        mod_resample_obj * mod_resample_pfs_object;
        con_hops_obj * con_hops_seps_rs_object;
        con_hops_obj * con_hops_pfs_rs_object;

        mod_volume_obj * mod_volume_seps_object;
        mod_volume_obj * mod_volume_pfs_object;
        con_hops_obj * con_hops_seps_vol_object;
        con_hops_obj * con_hops_pfs_vol_object;
        snk_hops_obj * snk_hops_seps_vol_object;
        snk_hops_obj * snk_hops_pfs_vol_object;

        mod_classify_obj * mod_classify_object;
        con_categories_obj * con_categories_object;
        snk_categories_obj * snk_categories_object;

    } objects;   

    typedef struct aobjects {
      
        unsigned int nMessages;

        asrc_hops_obj * asrc_hops_mics_object;
        acon_hops_obj * acon_hops_mics_raw_object; 

        amod_mapping_obj * amod_mapping_mics_object;
        acon_hops_obj * acon_hops_mics_map_object;              

        amod_resample_obj * amod_resample_mics_object;
        acon_hops_obj * acon_hops_mics_rs_object;

        amod_stft_obj * amod_stft_mics_object;
        acon_spectra_obj * acon_spectra_mics_object;

        amod_noise_obj * amod_noise_mics_object;
        acon_powers_obj * acon_powers_mics_object;

        amod_ssl_obj * amod_ssl_object;
        asnk_pots_obj * asnk_pots_ssl_object;
        acon_pots_obj * acon_pots_ssl_object;

        ainj_targets_obj * ainj_targets_sst_object;
        acon_targets_obj * acon_targets_sst_object;

        amod_sst_obj * amod_sst_object;
        asnk_tracks_obj * asnk_tracks_sst_object;
        acon_tracks_obj * acon_tracks_sst_object;

        amod_sss_obj * amod_sss_object;
        acon_spectra_obj * acon_spectra_seps_object;
        acon_spectra_obj * acon_spectra_pfs_object;

        amod_istft_obj * amod_istft_seps_object;
        amod_istft_obj * amod_istft_pfs_object;
        acon_hops_obj * acon_hops_seps_object;
        acon_hops_obj * acon_hops_pfs_object;

        amod_resample_obj * amod_resample_seps_object;
        amod_resample_obj * amod_resample_pfs_object;
        acon_hops_obj * acon_hops_seps_rs_object;
        acon_hops_obj * acon_hops_pfs_rs_object;

        amod_volume_obj * amod_volume_seps_object;
        amod_volume_obj * amod_volume_pfs_object;
        acon_hops_obj * acon_hops_seps_vol_object;
        acon_hops_obj * acon_hops_pfs_vol_object;
        asnk_hops_obj * asnk_hops_seps_vol_object;
        asnk_hops_obj * asnk_hops_pfs_vol_object;

        amod_classify_obj * amod_classify_object;
        acon_categories_obj * acon_categories_object;
        asnk_categories_obj * asnk_categories_object;

    } aobjects;
 
    objects * objects_construct(const configs * cfgs);

    void objects_destroy(objects * objs);

    aobjects * aobjects_construct(const configs * cfgs);

    void aobjects_destroy(aobjects * objs);

#endif