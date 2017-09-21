
    #include "configs.h"

    configs * configs_construct(const char * file_config, const char * file_ios) {

        configs * cfgs;
        unsigned int iSink;

        cfgs = (configs *) malloc(sizeof(configs));

        // +----------------------------------------------------------+
        // | Raw                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Source                                               |
            // +------------------------------------------------------+  

                cfgs->src_hops_raw_config = parameters_src_hops_raw_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_raw_config = parameters_msg_hops_raw_config(file_config, file_ios);
            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                cfgs->snk_hops_raw_config_count = parameters_snk_hops_raw_count(file_config, file_ios);
                cfgs->snk_hops_raw_configs = (snk_hops_cfg **) malloc(sizeof(snk_hops_cfg *) * cfgs->snk_hops_raw_config_count);

                for (iSink = 0; iSink < cfgs->snk_hops_raw_config_count; iSink++) {

                    cfgs->snk_hops_raw_configs[iSink] = parameters_snk_hops_raw_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | Mapping                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_mapping_config = parameters_mod_mapping_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_mapping_config = parameters_msg_hops_mapping_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+   

                cfgs->snk_hops_mapping_config_count = parameters_snk_hops_mapping_count(file_config, file_ios);
                cfgs->snk_hops_mapping_configs = (snk_hops_cfg **) malloc(sizeof(snk_hops_cfg *) * cfgs->snk_hops_mapping_config_count);

                for (iSink = 0; iSink < cfgs->snk_hops_mapping_config_count; iSink++) {

                    cfgs->snk_hops_mapping_configs[iSink] = parameters_snk_hops_mapping_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | Resample                                                 |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_resample_config = parameters_mod_resample_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_hops_resample_config = parameters_msg_hops_resample_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_hops_resample_config_count = parameters_snk_hops_resample_count(file_config, file_ios);
                cfgs->snk_hops_resample_configs = (snk_hops_cfg **) malloc(sizeof(snk_hops_cfg *) * cfgs->snk_hops_resample_config_count);

                for (iSink = 0; iSink < cfgs->snk_hops_resample_config_count; iSink++) {

                    cfgs->snk_hops_resample_configs[iSink] = parameters_snk_hops_resample_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | STFT                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_stft_config = parameters_mod_stft_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_spectra_stft_config = parameters_msg_spectra_stft_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_spectra_stft_config_count = parameters_snk_spectra_stft_count(file_config, file_ios);
                cfgs->snk_spectra_stft_configs = (snk_spectra_cfg **) malloc(sizeof(snk_spectra_cfg *) * cfgs->snk_spectra_stft_config_count);

                for (iSink = 0; iSink < cfgs->snk_spectra_stft_config_count; iSink++) {

                    cfgs->snk_spectra_stft_configs[iSink] = parameters_snk_spectra_stft_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | SSL                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_ssl_config = parameters_mod_ssl_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_pots_ssl_config = parameters_msg_pots_ssl_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_pots_ssl_config_count = parameters_snk_pots_ssl_count(file_config, file_ios);
                cfgs->snk_pots_ssl_configs = (snk_pots_cfg **) malloc(sizeof(snk_pots_cfg *) * cfgs->snk_pots_ssl_config_count);

                for (iSink = 0; iSink < cfgs->snk_pots_ssl_config_count; iSink++) {

                    cfgs->snk_pots_ssl_configs[iSink] = parameters_snk_pots_ssl_config(file_config, file_ios, iSink);

                }

        // +----------------------------------------------------------+
        // | SST                                                      |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                cfgs->mod_sst_config = parameters_mod_sst_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                cfgs->msg_tracks_sst_config = parameters_msg_tracks_sst_config(file_config, file_ios);

            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+  

                cfgs->snk_tracks_sst_config_count = parameters_snk_tracks_sst_count(file_config, file_ios);
                cfgs->snk_tracks_sst_configs = (snk_tracks_cfg **) malloc(sizeof(snk_tracks_cfg *) * cfgs->snk_tracks_sst_config_count);

                for (iSink = 0; iSink < cfgs->snk_tracks_sst_config_count; iSink++) {

                    cfgs->snk_tracks_sst_configs[iSink] = parameters_snk_tracks_sst_config(file_config, file_ios, iSink);

                }
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

                src_hops_cfg_destroy(cfgs->src_hops_raw_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_raw_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_hops_raw_config_count; iSink++) {

                    snk_hops_cfg_destroy(cfgs->snk_hops_raw_configs[iSink]);

                }

                free((void *) cfgs->snk_hops_raw_configs);

        // +----------------------------------------------------------+
        // | Mapping                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_mapping_cfg_destroy(cfgs->mod_mapping_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_mapping_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_hops_mapping_config_count; iSink++) {

                    snk_hops_cfg_destroy(cfgs->snk_hops_mapping_configs[iSink]);

                }

                free((void *) cfgs->snk_hops_mapping_configs);

        // +----------------------------------------------------------+
        // | Mapping                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_resample_cfg_destroy(cfgs->mod_resample_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_hops_cfg_destroy(cfgs->msg_hops_resample_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_hops_resample_config_count; iSink++) {

                    snk_hops_cfg_destroy(cfgs->snk_hops_resample_configs[iSink]);

                }

                free((void *) cfgs->snk_hops_resample_configs);

        // +----------------------------------------------------------+
        // | STFT                                                     |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Module                                               |
            // +------------------------------------------------------+  

                mod_stft_cfg_destroy(cfgs->mod_stft_config);
                
            // +------------------------------------------------------+
            // | Message                                              |
            // +------------------------------------------------------+  

                msg_spectra_cfg_destroy(cfgs->msg_spectra_stft_config);
                            
            // +------------------------------------------------------+
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_spectra_stft_config_count; iSink++) {

                    snk_spectra_cfg_destroy(cfgs->snk_spectra_stft_configs[iSink]);

                }

                free((void *) cfgs->snk_spectra_stft_configs);

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
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_pots_ssl_config_count; iSink++) {

                    snk_pots_cfg_destroy(cfgs->snk_pots_ssl_configs[iSink]);

                }

                free((void *) cfgs->snk_pots_ssl_configs);

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
            // | Sinks                                                |
            // +------------------------------------------------------+                 
            
                for (iSink = 0; iSink < cfgs->snk_tracks_sst_config_count; iSink++) {

                    snk_tracks_cfg_destroy(cfgs->snk_tracks_sst_configs[iSink]);

                }

                free((void *) cfgs->snk_tracks_sst_configs);
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
