#ifndef __DEMO_PARAMETERS
#define __DEMO_PARAMETERS

    #include <odas/odas.h>
    #include <libconfig.h>
    
    int parameters_lookup_int(const char * file, const char * path);

    float parameters_lookup_float(const char * file, const char * path);

    char * parameters_lookup_string(const char * file, const char * path);

    unsigned int parameters_count(const char * file, const char * path);


    src_hops_cfg * parameters_src_hops_raw_config(const char * fileConfig, const char * fileIOs);

    msg_hops_cfg * parameters_msg_hops_raw_config(const char * fileConfig, const char * fileIOs);
    
    unsigned int parameters_snk_hops_raw_count(const char * fileConfig, const char * fileIOs);

    snk_hops_cfg * parameters_snk_hops_raw_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_mapping_cfg * parameters_mod_mapping_config(const char * fileConfig, const char * fileIOs);

    msg_hops_cfg * parameters_msg_hops_mapping_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_hops_mapping_count(const char * fileConfig, const char * fileIOs);

    snk_hops_cfg * parameters_snk_hops_mapping_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_resample_cfg * parameters_mod_resample_config(const char * fileConfig, const char * fileIOs);

    msg_hops_cfg * parameters_msg_hops_resample_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_hops_resample_count(const char * fileConfig, const char * fileIOs);

    snk_hops_cfg * parameters_snk_hops_resample_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_stft_cfg * parameters_mod_stft_config(const char * fileConfig, const char * fileIOs);

    msg_spectra_cfg * parameters_msg_spectra_stft_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_spectra_stft_count(const char * fileConfig, const char * fileIOs);

    snk_spectra_cfg * parameters_snk_spectra_stft_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_ssl_cfg * parameters_mod_ssl_config(const char * fileConfig, const char * fileIOs);

    msg_pots_cfg * parameters_msg_pots_ssl_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_pots_ssl_count(const char * fileConfig, const char * fileIOs);

    snk_pots_cfg * parameters_snk_pots_ssl_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_sst_cfg * parameters_mod_sst_config(const char * fileConfig, const char * fileIOs);

    msg_tracks_cfg * parameters_msg_tracks_sst_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_tracks_sst_count(const char * fileConfig, const char * fileIOs);

    snk_tracks_cfg * parameters_snk_tracks_sst_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    /*
    mod_sss_cfg * parameters_mod_sss_config(const char * fileConfig, const char * fileIOs);

    msg_spectra_cfg * parameters_msg_spectra_sss_config(const char * fileConfig, const char * fileIOs);

    msg_envs_cfg * parameters_msg_envs_sss_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_spectra_sss_count(const char * fileConfig, const char * fileIOs);

    snk_spectra_cfg * parameters_snk_spectra_sss_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_sspf_cfg * parameters_mod_sspf_config(const char * fileConfig, const char * fileIOs);

    msg_spectra_cfg * parameters_msg_spectra_sspf_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_spectra_sspf_count(const char * fileConfig, const char * fileIOs);

    snk_spectra_cfg * parameters_snk_spectra_sspf_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_istft_cfg * parameters_mod_istft_config(const char * fileConfig, const char * fileIOs);

    msg_hops_cfg * parameters_msg_hops_istft_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_hops_istft_count(const char * fileConfig, const char * fileIOs);

    snk_hops_cfg * parameters_snk_hops_istft_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);


    mod_gain_cfg * parameters_mod_gain_config(const char * fileConfig, const char * fileIOs);

    msg_hops_cfg * parameters_msg_hops_gain_config(const char * fileConfig, const char * fileIOs);

    unsigned int parameters_snk_hops_gain_count(const char * fileConfig, const char * fileIOs);

    snk_hops_cfg * parameters_snk_hops_gain_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink);
    */

#endif