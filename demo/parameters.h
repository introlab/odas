#ifndef __DEMO_PARAMETERS
#define __DEMO_PARAMETERS

    #include <odas/odas.h>
    #include <libconfig.h>
    
    int parameters_lookup_int(const char * file, const char * path);

    float parameters_lookup_float(const char * file, const char * path);

    char * parameters_lookup_string(const char * file, const char * path);

    unsigned int parameters_count(const char * file, const char * path);


    src_hops_cfg * parameters_src_hops_mics_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_mics_raw_config(const char * fileConfig);


    mod_mapping_cfg * parameters_mod_mapping_mics_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_mics_map_config(const char * fileConfig);


    mod_resample_cfg * parameters_mod_resample_mics_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_mics_rs_config(const char * fileConfig);


    mod_stft_cfg * parameters_mod_stft_mics_config(const char * fileConfig);

    msg_spectra_cfg * parameters_msg_spectra_mics_config(const char * fileConfig);


    mod_noise_cfg * parameters_mod_noise_mics_config(const char * fileConfig);

    msg_powers_cfg * parameters_msg_powers_mics_config(const char * fileConfig);


    mod_ssl_cfg * parameters_mod_ssl_config(const char * fileConfig);

    msg_pots_cfg * parameters_msg_pots_ssl_config(const char * fileConfig);

    snk_pots_cfg * parameters_snk_pots_ssl_config(const char * fileConfig);


    inj_targets_cfg * parameters_inj_targets_sst_config(const char * fileConfig);

    msg_targets_cfg * parameters_msg_targets_sst_config(const char * fileConfig);


    mod_sst_cfg * parameters_mod_sst_config(const char * fileConfig);

    msg_tracks_cfg * parameters_msg_tracks_sst_config(const char * fileConfig);

    snk_tracks_cfg * parameters_snk_tracks_sst_config(const char * fileConfig);


    mod_sss_cfg * parameters_mod_sss_config(const char * fileConfig);

    msg_spectra_cfg * parameters_msg_spectra_seps_config(const char * fileConfig);

    msg_spectra_cfg * parameters_msg_spectra_pfs_config(const char * fileConfig);


    mod_istft_cfg * parameters_mod_istft_seps_config(const char * fileConfig);

    mod_istft_cfg * parameters_mod_istft_pfs_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_seps_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_pfs_config(const char * fileConfig);
    

    mod_resample_cfg * parameters_mod_resample_seps_config(const char * fileConfig);

    mod_resample_cfg * parameters_mod_resample_pfs_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_seps_rs_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_pfs_rs_config(const char * fileConfig);


    mod_volume_cfg * parameters_mod_volume_seps_config(const char * fileConfig);

    mod_volume_cfg * parameters_mod_volume_pfs_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_seps_vol_config(const char * fileConfig);

    msg_hops_cfg * parameters_msg_hops_pfs_vol_config(const char * fileConfig);

    snk_hops_cfg * parameters_snk_hops_seps_vol_config(const char * fileConfig);

    snk_hops_cfg * parameters_snk_hops_pfs_vol_config(const char * fileConfig);


    mod_classify_cfg * parameters_mod_classify_config(const char * fileConfig);

    msg_categories_cfg * parameters_msg_categories_config(const char * fileConfig);

    snk_categories_cfg * parameters_snk_categories_config(const char * fileConfig);

#endif