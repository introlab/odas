
    #include "configs.h"

    configs * configs_construct(const char * file_config) {

        configs * cfgs;
        unsigned int iSink;

        cfgs = (configs *) malloc(sizeof(configs));

        // +----------------------------------------------------------+
        // | Raw                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Source                                               |
            // +------------------------------------------------------+  

                cfgs->src_hops_mics_config = parameters_src_hops_mics_config(file_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_mics_raw_config = parameters_msg_hops_mics_raw_config(file_config);

        // +----------------------------------------------------------+
        // | Mapping                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_mapping_mics_config = parameters_mod_mapping_mics_config(file_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_mics_map_config = parameters_msg_hops_mics_map_config(file_config);


        // +----------------------------------------------------------+
        // | Resample                                                 |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_resample_mics_config = parameters_mod_resample_mics_config(file_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_mics_rs_config = parameters_msg_hops_mics_rs_config(file_config);

        // +----------------------------------------------------------+
        // | STFT                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_stft_mics_config = parameters_mod_stft_mics_config(file_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_spectra_mics_config = parameters_msg_spectra_mics_config(file_config);


        // +----------------------------------------------------------+
        // | SSL                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_ssl_config = parameters_mod_ssl_config(file_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_pots_ssl_config = parameters_msg_pots_ssl_config(file_config);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_pots_ssl_config = parameters_snk_pots_ssl_config(file_config);


        // +----------------------------------------------------------+
        // | SST                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_sst_config = parameters_mod_sst_config(file_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_tracks_sst_config = parameters_msg_tracks_sst_config(file_config);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_tracks_sst_config = parameters_snk_tracks_sst_config(file_config);

/*
        // +----------------------------------------------------------+
        // | SSS                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_sss_config = parameters_mod_sss_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_spectra_sss_config = parameters_msg_spectra_sss_config(file_config, file_ios);
                cfgs->msg_envs_sss_config = parameters_msg_envs_sss_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_spectra_sss_config_count = parameters_snk_spectra_sss_count(file_config, file_ios);
                cfgs->snk_spectra_sss_configs = (snk_spectra_cfg **) malloc(sizeof(snk_spectra_cfg *) * cfgs->snk_spectra_sss_config_count);

                for (iSink = 0; iSink < cfgs->snk_spectra_sss_config_count; iSink++) {

                    cfgs->snk_spectra_sss_configs[iSink] = parameters_snk_spectra_sss_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | SSPF                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_sspf_config = parameters_mod_sspf_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_spectra_sspf_config = parameters_msg_spectra_sspf_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_spectra_sspf_config_count = parameters_snk_spectra_sspf_count(file_config, file_ios);
                cfgs->snk_spectra_sspf_configs = (snk_spectra_cfg **) malloc(sizeof(snk_spectra_cfg *) * cfgs->snk_spectra_sspf_config_count);

                for (iSink = 0; iSink < cfgs->snk_spectra_sspf_config_count; iSink++) {

                    cfgs->snk_spectra_sspf_configs[iSink] = parameters_snk_spectra_sspf_config(file_config, file_ios, iSink);

                }


        // +----------------------------------------------------------+
        // | ISTFT                                                    |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_istft_config = parameters_mod_istft_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_istft_config = parameters_msg_hops_istft_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_hops_istft_config_count = parameters_snk_hops_istft_count(file_config, file_ios);
                cfgs->snk_hops_istft_configs = (snk_hops_cfg **) malloc(sizeof(snk_hops_cfg *) * cfgs->snk_hops_istft_config_count);

                for (iSink = 0; iSink < cfgs->snk_hops_istft_config_count; iSink++) {

                    cfgs->snk_hops_istft_configs[iSink] = parameters_snk_hops_istft_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | Gain                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_gain_config = parameters_mod_gain_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_gain_config = parameters_msg_hops_gain_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_hops_gain_config_count = parameters_snk_hops_gain_count(file_config, file_ios);
                cfgs->snk_hops_gain_configs = (snk_hops_cfg **) malloc(sizeof(snk_hops_cfg *) * cfgs->snk_hops_gain_config_count);

                for (iSink = 0; iSink < cfgs->snk_hops_gain_config_count; iSink++) {

                    cfgs->snk_hops_gain_configs[iSink] = parameters_snk_hops_gain_config(file_config, file_ios, iSink);

                }
*/
        return cfgs;

    }

    void configs_destroy(configs * cfgs) {

        unsigned int iSink;

        // +----------------------------------------------------------+
        // | Raw                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Source                                               |
            // +------------------------------------------------------+  

                src_hops_cfg_destroy(cfgs->src_hops_mics_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_mics_raw_config);
                            
        // +----------------------------------------------------------+
        // | Mapping                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_mapping_cfg_destroy(cfgs->mod_mapping_mics_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_mics_map_config);
                            
        // +----------------------------------------------------------+
        // | Mapping                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_resample_cfg_destroy(cfgs->mod_resample_mics_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_mics_rs_config);
  
        // +----------------------------------------------------------+
        // | STFT                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_stft_cfg_destroy(cfgs->mod_stft_mics_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_spectra_cfg_destroy(cfgs->msg_spectra_mics_config);
                            
        // +----------------------------------------------------------+
        // | SSL                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_ssl_cfg_destroy(cfgs->mod_ssl_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_pots_cfg_destroy(cfgs->msg_pots_ssl_config);
                            
            // +------------------------------------------------------+
            // | Sink                                                 |
            // +------------------------------------------------------+                 
            
                snk_pots_cfg_destroy(cfgs->snk_pots_ssl_config);

        // +----------------------------------------------------------+
        // | SST                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_sst_cfg_destroy(cfgs->mod_sst_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_tracks_cfg_destroy(cfgs->msg_tracks_sst_config);
                            
            // +------------------------------------------------------+
            // | Sink                                                 |
            // +------------------------------------------------------+                 
            
                snk_tracks_cfg_destroy(cfgs->snk_tracks_sst_config);
/*
        // +----------------------------------------------------------+
        // | SSS                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_sss_cfg_destroy(cfgs->mod_sss_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_spectra_cfg_destroy(cfgs->msg_spectra_sss_config);
                msg_envs_cfg_destroy(cfgs->msg_envs_sss_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_spectra_sss_config_count; iSink++) {

                    snk_spectra_cfg_destroy(cfgs->snk_spectra_sss_configs[iSink]);

                }

                free((void *) cfgs->snk_spectra_sss_configs);

        // +----------------------------------------------------------+
        // | SSPF                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_sspf_cfg_destroy(cfgs->mod_sspf_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_spectra_cfg_destroy(cfgs->msg_spectra_sspf_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_spectra_sspf_config_count; iSink++) {

                    snk_spectra_cfg_destroy(cfgs->snk_spectra_sspf_configs[iSink]);

                }
                
                free((void *) cfgs->snk_spectra_sspf_configs);

        // +----------------------------------------------------------+
        // | ISTFT                                                    |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_istft_cfg_destroy(cfgs->mod_istft_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_istft_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_hops_istft_config_count; iSink++) {

                    snk_hops_cfg_destroy(cfgs->snk_hops_istft_configs[iSink]);

                }
                
                free((void *) cfgs->snk_hops_istft_configs);

        // +----------------------------------------------------------+
        // | Gain                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_gain_cfg_destroy(cfgs->mod_gain_config);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_gain_config);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                for (iSink = 0; iSink < cfgs->snk_hops_gain_config_count; iSink++) {

                    snk_hops_cfg_destroy(cfgs->snk_hops_gain_configs[iSink]);

                }

                free((void *) cfgs->snk_hops_gain_configs);
*/
        free((void *) cfgs);

    }
