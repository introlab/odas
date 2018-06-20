#ifndef __ODAS_DEMO_CORE_OBJECTS
#define __ODAS_DEMO_CORE_OBJECTS

    #include <odas/odas.h>
    #include <stdlib.h>

    #include "configs.h"

    typedef struct objects {

        src_hops_obj * src_hops_in_raw;
        con_hops_obj * con_hops_in_raw;
        snk_hops_obj * snk_hops_in_raw;

        src_targets_obj * src_targets_in_raw;
        con_targets_obj * con_targets_in_raw;

        mod_mapping_obj * mod_mapping_in;
        con_hops_obj * con_hops_in_map;

        mod_resample_obj * mod_resample_in;
        con_hops_obj * con_hops_in_rs;

        mod_align_obj * mod_align_in;
        con_targets_obj * con_targets_in_rs;

        mod_stft_obj * mod_stft_in;
        con_spectra_obj * con_spectra_in;

        mod_noise_obj * mod_noise_in;
        con_powers_obj * con_powers_in;

        mod_ssl_obj * mod_ssl;
        con_pots_obj * con_pots;
        snk_pots_obj * snk_pots;

        mod_sst_obj * mod_sst;
        con_tracks_obj * con_tracks;
        snk_tracks_obj * snk_tracks;

        mod_lag_obj * mod_lag;
        con_spectra_obj * con_spectra_lag;

        mod_sss_obj * mod_sss;
        con_spectra_obj * con_spectra_out_sep;
        con_spectra_obj * con_spectra_out_pf;

        mod_istft_obj * mod_istft_out_sep;
        con_hops_obj * con_hops_out_sep;
        mod_resample_obj * mod_resample_out_seprs;
        con_hops_obj * con_hops_out_seprs;
        snk_hops_obj * snk_hops_out_seprs;

        mod_istft_obj * mod_istft_out_pf;
        con_hops_obj * con_hops_out_pf;
        mod_resample_obj * mod_resample_out_pfrs;
        con_hops_obj * con_hops_out_pfrs;
        snk_hops_obj * snk_hops_out_pfrs;

    } objects;

    typedef struct aobjects {

        asrc_hops_obj * asrc_hops_in_raw;
        acon_hops_obj * acon_hops_in_raw;
        asnk_hops_obj * asnk_hops_in_raw;

        asrc_targets_obj * asrc_targets_in_raw;
        acon_targets_obj * acon_targets_in_raw;

        amod_mapping_obj * amod_mapping_in;
        acon_hops_obj * acon_hops_in_map;

        amod_resample_obj * amod_resample_in;
        acon_hops_obj * acon_hops_in_rs;

        amod_align_obj * amod_align_in;
        acon_targets_obj * acon_targets_in_rs;

        amod_stft_obj * amod_stft_in;
        acon_spectra_obj * acon_spectra_in;

        amod_noise_obj * amod_noise_in;
        acon_powers_obj * acon_powers_in;

        amod_ssl_obj * amod_ssl;
        acon_pots_obj * acon_pots;
        asnk_pots_obj * asnk_pots;

        amod_sst_obj * amod_sst;
        acon_tracks_obj * acon_tracks;
        asnk_tracks_obj * asnk_tracks;

        amod_lag_obj * amod_lag;
        acon_spectra_obj * acon_spectra_lag;

        amod_sss_obj * amod_sss;
        acon_spectra_obj * acon_spectra_out_sep;
        acon_spectra_obj * acon_spectra_out_pf;

        amod_istft_obj * amod_istft_out_sep;
        acon_hops_obj * acon_hops_out_sep;
        amod_resample_obj * amod_resample_out_seprs;
        acon_hops_obj * acon_hops_out_seprs;
        asnk_hops_obj * asnk_hops_out_seprs;

        amod_istft_obj * amod_istft_out_pf;
        acon_hops_obj * acon_hops_out_pf;
        amod_resample_obj * amod_resample_out_pfrs;
        acon_hops_obj * acon_hops_out_pfrs;
        asnk_hops_obj * asnk_hops_out_pfrs;

    } aobjects;

    objects * objects_construct(configs * cfgs);

    void objects_destroy(objects * objs);

    void objects_process(objects * objs);

    aobjects * aobjects_construct(configs * cfgs);

    void aobjects_destroy(aobjects * objs);

    void aobjects_process(aobjects * objs);

#endif