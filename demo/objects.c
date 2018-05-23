    
    #include "objects.h"

    objects * objects_construct(const configs * cfgs) {

        objects * objs;
        unsigned int iSink;

        objs = (objects *) malloc(sizeof(objects));

        // +----------------------------------------------------------+
        // | Construct                                                |
        // +----------------------------------------------------------+

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    objs->src_hops_mics_object = src_hops_construct(cfgs->src_hops_mics_config, 
                                                                    cfgs->msg_hops_mics_raw_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_hops_mics_raw_object = con_hops_construct(1, cfgs->msg_hops_mics_raw_config);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_mapping_mics_object = mod_mapping_construct(cfgs->mod_mapping_mics_config, 
                                                                          cfgs->msg_hops_mics_map_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_hops_mics_map_object = con_hops_construct(1, cfgs->msg_hops_mics_map_config);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_resample_mics_object = mod_resample_construct(cfgs->mod_resample_mics_config, 
                                                                            cfgs->msg_hops_mics_map_config, 
                                                                            cfgs->msg_hops_mics_rs_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_hops_mics_rs_object = con_hops_construct(2, cfgs->msg_hops_mics_rs_config);                    

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_stft_mics_object = mod_stft_construct(cfgs->mod_stft_mics_config, 
                                                                    cfgs->msg_hops_mics_rs_config, 
                                                                    cfgs->msg_spectra_mics_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_spectra_mics_object = con_spectra_construct(3, cfgs->msg_spectra_mics_config);

            // +------------------------------------------------------+
            // | Noise                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_noise_mics_object = mod_noise_construct(cfgs->mod_noise_mics_config, 
                                                                      cfgs->msg_spectra_mics_config, 
                                                                      cfgs->msg_powers_mics_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_powers_mics_object = con_powers_construct(1, cfgs->msg_powers_mics_config);

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  
                    
                    objs->mod_ssl_object = mod_ssl_construct(cfgs->mod_ssl_config, 
                                                             cfgs->msg_spectra_mics_config,
                                                             cfgs->msg_pots_ssl_config);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_pots_ssl_object = snk_pots_construct(cfgs->snk_pots_ssl_config, 
                                                                   cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+ 

                objs->con_pots_ssl_object = con_pots_construct(2, cfgs->msg_pots_ssl_config);

            // +------------------------------------------------------+
            // | Target                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Injector                                         |
                // +--------------------------------------------------+  

                    objs->inj_targets_sst_object = inj_targets_construct(cfgs->inj_targets_sst_config, 
                                                                         cfgs->msg_hops_mics_rs_config, 
                                                                         cfgs->msg_targets_sst_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+              

                    objs->con_targets_sst_object = con_targets_construct(1, cfgs->msg_targets_sst_config);

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_sst_object = mod_sst_construct(cfgs->mod_sst_config, 
                                                             cfgs->mod_ssl_config, 
                                                             cfgs->msg_pots_ssl_config, 
                                                             cfgs->msg_targets_sst_config,
                                                             cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_tracks_sst_object = snk_tracks_construct(cfgs->snk_tracks_sst_config, 
                                                                       cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+                    

                    objs->con_tracks_sst_object = con_tracks_construct(3, cfgs->msg_tracks_sst_config);

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_sss_object = mod_sss_construct(cfgs->mod_sss_config, 
                                                             cfgs->msg_tracks_sst_config, 
                                                             cfgs->msg_spectra_mics_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+                    

                    objs->con_spectra_seps_object = con_spectra_construct(1, cfgs->msg_spectra_seps_config);
                    objs->con_spectra_pfs_object = con_spectra_construct(1, cfgs->msg_spectra_pfs_config);

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_istft_seps_object = mod_istft_construct(cfgs->mod_istft_seps_config, 
                                                                      cfgs->msg_spectra_seps_config, 
                                                                      cfgs->msg_hops_seps_config);

                    objs->mod_istft_pfs_object = mod_istft_construct(cfgs->mod_istft_pfs_config, 
                                                                     cfgs->msg_spectra_pfs_config, 
                                                                     cfgs->msg_hops_pfs_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+                     

                    objs->con_hops_seps_object = con_hops_construct(2, cfgs->msg_hops_seps_config);
                    objs->con_hops_pfs_object = con_hops_construct(1, cfgs->msg_hops_pfs_config);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_resample_seps_object = mod_resample_construct(cfgs->mod_resample_seps_config, 
                                                                            cfgs->msg_hops_seps_config, 
                                                                            cfgs->msg_hops_seps_rs_config);

                    objs->mod_resample_pfs_object = mod_resample_construct(cfgs->mod_resample_pfs_config, 
                                                                           cfgs->msg_hops_pfs_config, 
                                                                           cfgs->msg_hops_pfs_rs_config);       

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_hops_seps_rs_object = con_hops_construct(1, cfgs->msg_hops_seps_rs_config);
                    objs->con_hops_pfs_rs_object = con_hops_construct(1, cfgs->msg_hops_pfs_rs_config);

            // +------------------------------------------------------+
            // | Volume                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_volume_seps_object = mod_volume_construct(cfgs->mod_volume_seps_config, 
                                                                        cfgs->msg_hops_seps_vol_config);

                    objs->mod_volume_pfs_object = mod_volume_construct(cfgs->mod_volume_pfs_config, 
                                                                       cfgs->msg_hops_pfs_vol_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_hops_seps_vol_object = con_hops_construct(1, cfgs->msg_hops_seps_vol_config);
                    objs->con_hops_pfs_vol_object = con_hops_construct(1, cfgs->msg_hops_pfs_vol_config);

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                     

                    objs->snk_hops_seps_vol_object = snk_hops_construct(cfgs->snk_hops_seps_vol_config, 
                                                                        cfgs->msg_hops_seps_vol_config);

                    objs->snk_hops_pfs_vol_object = snk_hops_construct(cfgs->snk_hops_pfs_vol_config, 
                                                                       cfgs->msg_hops_pfs_vol_config);

            // +------------------------------------------------------+
            // | Classify                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_classify_object = mod_classify_construct(cfgs->mod_classify_config,
                                                                       cfgs->msg_hops_seps_config,
                                                                       cfgs->msg_tracks_sst_config,
                                                                       cfgs->msg_categories_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->con_categories_object = con_categories_construct(1, cfgs->msg_categories_config);
                
                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    objs->snk_categories_object = snk_categories_construct(cfgs->snk_categories_config,
                                                                           cfgs->msg_categories_config);

        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+              

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    src_hops_connect(objs->src_hops_mics_object, 
                                     objs->con_hops_mics_raw_object->in);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_mapping_connect(objs->mod_mapping_mics_object, 
                                        objs->con_hops_mics_raw_object->outs[0], 
                                        objs->con_hops_mics_map_object->in);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_resample_connect(objs->mod_resample_mics_object, 
                                         objs->con_hops_mics_map_object->outs[0], 
                                         objs->con_hops_mics_rs_object->in);

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_stft_connect(objs->mod_stft_mics_object, 
                                     objs->con_hops_mics_rs_object->outs[0], 
                                     objs->con_spectra_mics_object->in);

            // +------------------------------------------------------+
            // | Noise                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_noise_connect(objs->mod_noise_mics_object,
                                      objs->con_spectra_mics_object->outs[0],
                                      objs->con_powers_mics_object->in);

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_ssl_connect(objs->mod_ssl_object, 
                                    objs->con_spectra_mics_object->outs[1], 
                                    objs->con_pots_ssl_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    snk_pots_connect(objs->snk_pots_ssl_object,
                                     objs->con_pots_ssl_object->outs[1]);

            // +------------------------------------------------------+
            // | Target                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Injector                                         |
                // +--------------------------------------------------+

                    inj_targets_connect(objs->inj_targets_sst_object,
                                        objs->con_hops_mics_rs_object->outs[1],
                                        objs->con_targets_sst_object->in);

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sst_connect(objs->mod_sst_object, 
                                    objs->con_pots_ssl_object->outs[0], 
                                    objs->con_targets_sst_object->outs[0],
                                    objs->con_tracks_sst_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    snk_tracks_connect(objs->snk_tracks_sst_object,
                                       objs->con_tracks_sst_object->outs[2]);

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sss_connect(objs->mod_sss_object,
                                    objs->con_spectra_mics_object->outs[2],
                                    objs->con_powers_mics_object->outs[0],
                                    objs->con_tracks_sst_object->outs[0],
                                    objs->con_spectra_seps_object->in,
                                    objs->con_spectra_pfs_object->in);

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+                      

                    mod_istft_connect(objs->mod_istft_seps_object,
                                      objs->con_spectra_seps_object->outs[0],
                                      objs->con_hops_seps_object->in);

                    mod_istft_connect(objs->mod_istft_pfs_object,
                                      objs->con_spectra_pfs_object->outs[0],
                                      objs->con_hops_pfs_object->in);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_resample_connect(objs->mod_resample_seps_object,
                                         objs->con_hops_seps_object->outs[0],
                                         objs->con_hops_seps_rs_object->in);

                    mod_resample_connect(objs->mod_resample_pfs_object,
                                         objs->con_hops_pfs_object->outs[0],
                                         objs->con_hops_pfs_rs_object->in);

            // +------------------------------------------------------+
            // | Volume                                               |
            // +------------------------------------------------------+ 

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_volume_connect(objs->mod_volume_seps_object,
                                       objs->con_hops_seps_rs_object->outs[0],
                                       objs->con_hops_seps_vol_object->in);

                    mod_volume_connect(objs->mod_volume_pfs_object,
                                       objs->con_hops_pfs_rs_object->outs[0],
                                       objs->con_hops_pfs_vol_object->in);

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    snk_hops_connect(objs->snk_hops_seps_vol_object,
                                     objs->con_hops_seps_vol_object->outs[0]);

                    snk_hops_connect(objs->snk_hops_pfs_vol_object,
                                     objs->con_hops_pfs_vol_object->outs[0]);

            // +------------------------------------------------------+
            // | Classify                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_classify_connect(objs->mod_classify_object,
                                         objs->con_hops_seps_object->outs[1],
                                         objs->con_tracks_sst_object->outs[1],
                                         objs->con_categories_object->in);

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+  

                    snk_categories_connect(objs->snk_categories_object,
                                           objs->con_categories_object->outs[0]);

        // +----------------------------------------------------------+
        // | Enable modules                                           |
        // +----------------------------------------------------------+  

            mod_mapping_enable(objs->mod_mapping_mics_object);
            mod_resample_enable(objs->mod_resample_mics_object);
            mod_stft_enable(objs->mod_stft_mics_object);

            if (cfgs->snk_pots_ssl_config->interface->type != interface_blackhole) {

                mod_ssl_enable(objs->mod_ssl_object);

            }

            if (cfgs->snk_tracks_sst_config->interface->type != interface_blackhole) {

                mod_ssl_enable(objs->mod_ssl_object);
                mod_sst_enable(objs->mod_sst_object);

            }

            if (cfgs->snk_hops_seps_vol_config->interface->type != interface_blackhole) {

                mod_ssl_enable(objs->mod_ssl_object);
                mod_sst_enable(objs->mod_sst_object);
                mod_noise_enable(objs->mod_noise_mics_object);
                mod_sss_enable(objs->mod_sss_object);
                mod_istft_enable(objs->mod_istft_seps_object);
                mod_resample_enable(objs->mod_resample_seps_object);
                mod_volume_enable(objs->mod_volume_seps_object);

            }

            if (cfgs->snk_hops_pfs_vol_config->interface->type != interface_blackhole) {

                mod_ssl_enable(objs->mod_ssl_object);
                mod_sst_enable(objs->mod_sst_object);
                mod_noise_enable(objs->mod_noise_mics_object);
                mod_sss_enable(objs->mod_sss_object);
                mod_istft_enable(objs->mod_istft_pfs_object);
                mod_resample_enable(objs->mod_resample_pfs_object);
                mod_volume_enable(objs->mod_volume_pfs_object);

            }

            if (cfgs->snk_categories_config->interface->type != interface_blackhole) {

                mod_ssl_enable(objs->mod_ssl_object);
                mod_sst_enable(objs->mod_sst_object);
                mod_noise_enable(objs->mod_noise_mics_object);
                mod_sss_enable(objs->mod_sss_object);
                mod_istft_enable(objs->mod_istft_seps_object);
                mod_classify_enable(objs->mod_classify_object);

            }

        return objs;

    }

    void objects_destroy(objects * objs) {

        unsigned int iSink;

        // +----------------------------------------------------------+
        // | Destroy                                                  |
        // +----------------------------------------------------------+

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    src_hops_destroy(objs->src_hops_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_mics_raw_object);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_mapping_destroy(objs->mod_mapping_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_mics_map_object);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_resample_destroy(objs->mod_resample_mics_object);
                                       
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_mics_rs_object);

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_stft_destroy(objs->mod_stft_mics_object);
                                        
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_spectra_destroy(objs->con_spectra_mics_object);

            // +------------------------------------------------------+
            // | Noise                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_noise_destroy(objs->mod_noise_mics_object);
                                        
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_powers_destroy(objs->con_powers_mics_object);

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_ssl_destroy(objs->mod_ssl_object);
                                       
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    snk_pots_destroy(objs->snk_pots_ssl_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_pots_destroy(objs->con_pots_ssl_object);

            // +------------------------------------------------------+
            // | Target                                               |
            // +------------------------------------------------------+ 

                // +--------------------------------------------------+
                // | Injector                                         |
                // +--------------------------------------------------+  

                    inj_targets_destroy(objs->inj_targets_sst_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_targets_destroy(objs->con_targets_sst_object);

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sst_destroy(objs->mod_sst_object);
                                        
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    snk_tracks_destroy(objs->snk_tracks_sst_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_tracks_destroy(objs->con_tracks_sst_object);

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sss_destroy(objs->mod_sss_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_spectra_destroy(objs->con_spectra_seps_object);
                    con_spectra_destroy(objs->con_spectra_pfs_object);                    

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+                      

                    mod_istft_destroy(objs->mod_istft_seps_object);
                    mod_istft_destroy(objs->mod_istft_pfs_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_seps_object);
                    con_hops_destroy(objs->con_hops_pfs_object);                     

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_resample_destroy(objs->mod_resample_seps_object);
                    mod_resample_destroy(objs->mod_resample_pfs_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_seps_rs_object);
                    con_hops_destroy(objs->con_hops_pfs_rs_object);                     

            // +------------------------------------------------------+
            // | Volume                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_volume_destroy(objs->mod_volume_seps_object);
                    mod_volume_destroy(objs->mod_volume_pfs_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_seps_vol_object);
                    con_hops_destroy(objs->con_hops_pfs_vol_object);       

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    snk_hops_destroy(objs->snk_hops_seps_vol_object);
                    snk_hops_destroy(objs->snk_hops_pfs_vol_object);

            // +------------------------------------------------------+
            // | Classify                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_classify_destroy(objs->mod_classify_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_categories_destroy(objs->con_categories_object);
                
                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    snk_categories_destroy(objs->snk_categories_object);

        free((void *) objs);

    }

    aobjects * aobjects_construct(const configs * cfgs) {

        aobjects * objs;
        unsigned int iSink;

        objs = (aobjects *) malloc(sizeof(aobjects));

        objs->nMessages = 100;

        // +----------------------------------------------------------+
        // | Construct                                                |
        // +----------------------------------------------------------+

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    objs->asrc_hops_mics_object = asrc_hops_construct(cfgs->src_hops_mics_config, 
                                                                      cfgs->msg_hops_mics_raw_config);
                
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+

                    objs->acon_hops_mics_raw_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_mics_raw_config);  

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_mapping_mics_object = amod_mapping_construct(cfgs->mod_mapping_mics_config, 
                                                                            cfgs->msg_hops_mics_map_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+

                    objs->acon_hops_mics_map_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_mics_map_config);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_resample_mics_object = amod_resample_construct(cfgs->mod_resample_mics_config, 
                                                                              cfgs->msg_hops_mics_map_config, 
                                                                              cfgs->msg_hops_mics_rs_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+

                    objs->acon_hops_mics_rs_object = acon_hops_construct(2, objs->nMessages, cfgs->msg_hops_mics_rs_config);

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_stft_mics_object = amod_stft_construct(cfgs->mod_stft_mics_config, 
                                                                      cfgs->msg_hops_mics_rs_config, 
                                                                      cfgs->msg_spectra_mics_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+
                    
                    objs->acon_spectra_mics_object = acon_spectra_construct(3, objs->nMessages, cfgs->msg_spectra_mics_config);

            // +------------------------------------------------------+
            // | Noise                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_noise_mics_object = amod_noise_construct(cfgs->mod_noise_mics_config, 
                                                                        cfgs->msg_spectra_mics_config, 
                                                                        cfgs->msg_powers_mics_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+
                    
                    objs->acon_powers_mics_object = acon_powers_construct(1, objs->nMessages, cfgs->msg_powers_mics_config);

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_ssl_object = amod_ssl_construct(cfgs->mod_ssl_config, 
                                                               cfgs->msg_spectra_mics_config, 
                                                               cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_pots_ssl_object = asnk_pots_construct(cfgs->snk_pots_ssl_config, 
                                                                     cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+

                    objs->acon_pots_ssl_object = acon_pots_construct(2, objs->nMessages, cfgs->msg_pots_ssl_config);

            // +------------------------------------------------------+
            // | Target                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Injector                                         |
                // +--------------------------------------------------+ 

                    objs->ainj_targets_sst_object = ainj_targets_construct(cfgs->inj_targets_sst_config, 
                                                                           cfgs->msg_hops_mics_rs_config, 
                                                                           cfgs->msg_targets_sst_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+              

                    objs->acon_targets_sst_object = acon_targets_construct(1, objs->nMessages, cfgs->msg_targets_sst_config);

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sst_object = amod_sst_construct(cfgs->mod_sst_config, 
                                                               cfgs->mod_ssl_config, 
                                                               cfgs->msg_pots_ssl_config, 
                                                               cfgs->msg_targets_sst_config,
                                                               cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_tracks_sst_object = asnk_tracks_construct(cfgs->snk_tracks_sst_config, 
                                                                         cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+

                    objs->acon_tracks_sst_object = acon_tracks_construct(3, objs->nMessages, cfgs->msg_tracks_sst_config);

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sss_object = amod_sss_construct(cfgs->mod_sss_config, 
                                                               cfgs->msg_tracks_sst_config, 
                                                               cfgs->msg_spectra_mics_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+                    

                    objs->acon_spectra_seps_object = acon_spectra_construct(1, objs->nMessages, cfgs->msg_spectra_seps_config);
                    objs->acon_spectra_pfs_object = acon_spectra_construct(1, objs->nMessages, cfgs->msg_spectra_pfs_config);

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_istft_seps_object = amod_istft_construct(cfgs->mod_istft_seps_config, 
                                                                        cfgs->msg_spectra_seps_config, 
                                                                        cfgs->msg_hops_seps_config);

                    objs->amod_istft_pfs_object = amod_istft_construct(cfgs->mod_istft_pfs_config, 
                                                                       cfgs->msg_spectra_pfs_config, 
                                                                       cfgs->msg_hops_pfs_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+                     

                    objs->acon_hops_seps_object = acon_hops_construct(2, objs->nMessages, cfgs->msg_hops_seps_config);
                    objs->acon_hops_pfs_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_pfs_config);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_resample_seps_object = amod_resample_construct(cfgs->mod_resample_seps_config, 
                                                                              cfgs->msg_hops_seps_config, 
                                                                              cfgs->msg_hops_seps_rs_config);

                    objs->amod_resample_pfs_object = amod_resample_construct(cfgs->mod_resample_pfs_config, 
                                                                             cfgs->msg_hops_pfs_config, 
                                                                             cfgs->msg_hops_pfs_rs_config);                                                                                   

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->acon_hops_seps_rs_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_seps_rs_config);

                    objs->acon_hops_pfs_rs_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_pfs_rs_config);

            // +------------------------------------------------------+
            // | Volume                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_volume_seps_object = amod_volume_construct(cfgs->mod_volume_seps_config, 
                                                                          cfgs->msg_hops_seps_vol_config);

                    objs->amod_volume_pfs_object = amod_volume_construct(cfgs->mod_volume_pfs_config, 
                                                                         cfgs->msg_hops_pfs_vol_config);                                                                                   

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->acon_hops_seps_vol_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_seps_vol_config);

                    objs->acon_hops_pfs_vol_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_pfs_vol_config);

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                     

                    objs->asnk_hops_seps_vol_object = asnk_hops_construct(cfgs->snk_hops_seps_vol_config, 
                                                                          cfgs->msg_hops_seps_vol_config);

                    objs->asnk_hops_pfs_vol_object = asnk_hops_construct(cfgs->snk_hops_pfs_vol_config, 
                                                                         cfgs->msg_hops_pfs_vol_config);

            // +------------------------------------------------------+
            // | Classify                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_classify_object = amod_classify_construct(cfgs->mod_classify_config,
                                                                         cfgs->msg_hops_seps_config,
                                                                         cfgs->msg_tracks_sst_config,
                                                                         cfgs->msg_categories_config);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    objs->acon_categories_object = acon_categories_construct(1, objs->nMessages, cfgs->msg_categories_config);
                
                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    objs->asnk_categories_object = asnk_categories_construct(cfgs->snk_categories_config,
                                                                             cfgs->msg_categories_config);

        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+  

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    asrc_hops_connect(objs->asrc_hops_mics_object, 
                                      objs->acon_hops_mics_raw_object->in);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_mapping_connect(objs->amod_mapping_mics_object, 
                                         objs->acon_hops_mics_raw_object->outs[0], 
                                         objs->acon_hops_mics_map_object->in);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_resample_connect(objs->amod_resample_mics_object, 
                                          objs->acon_hops_mics_map_object->outs[0], 
                                          objs->acon_hops_mics_rs_object->in);

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_stft_connect(objs->amod_stft_mics_object, 
                                      objs->acon_hops_mics_rs_object->outs[0], 
                                      objs->acon_spectra_mics_object->in);

            // +------------------------------------------------------+
            // | Noise                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_noise_connect(objs->amod_noise_mics_object,
                                       objs->acon_spectra_mics_object->outs[0],
                                       objs->acon_powers_mics_object->in);

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_ssl_connect(objs->amod_ssl_object, 
                                     objs->acon_spectra_mics_object->outs[1], 
                                     objs->acon_pots_ssl_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    asnk_pots_connect(objs->asnk_pots_ssl_object,
                                      objs->acon_pots_ssl_object->outs[1]);

            // +------------------------------------------------------+
            // | Target                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Injector                                         |
                // +--------------------------------------------------+  

                    ainj_targets_connect(objs->ainj_targets_sst_object,
                                         objs->acon_hops_mics_rs_object->outs[1],
                                         objs->acon_targets_sst_object->in);

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sst_connect(objs->amod_sst_object, 
                                     objs->acon_pots_ssl_object->outs[0], 
                                     objs->acon_targets_sst_object->outs[0],
                                     objs->acon_tracks_sst_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    asnk_tracks_connect(objs->asnk_tracks_sst_object,
                                        objs->acon_tracks_sst_object->outs[2]);

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sss_connect(objs->amod_sss_object,
                                     objs->acon_spectra_mics_object->outs[2],
                                     objs->acon_powers_mics_object->outs[0],
                                     objs->acon_tracks_sst_object->outs[0],
                                     objs->acon_spectra_seps_object->in,
                                     objs->acon_spectra_pfs_object->in);

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+                      

                    amod_istft_connect(objs->amod_istft_seps_object,
                                       objs->acon_spectra_seps_object->outs[0],
                                       objs->acon_hops_seps_object->in);

                    amod_istft_connect(objs->amod_istft_pfs_object,
                                       objs->acon_spectra_pfs_object->outs[0],
                                       objs->acon_hops_pfs_object->in);

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_resample_connect(objs->amod_resample_seps_object,
                                          objs->acon_hops_seps_object->outs[0],
                                          objs->acon_hops_seps_rs_object->in);

                    amod_resample_connect(objs->amod_resample_pfs_object,
                                          objs->acon_hops_pfs_object->outs[0],
                                          objs->acon_hops_pfs_rs_object->in);

            // +------------------------------------------------------+
            // | Volume                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_volume_connect(objs->amod_volume_seps_object,
                                        objs->acon_hops_seps_rs_object->outs[0],
                                        objs->acon_hops_seps_vol_object->in);

                    amod_volume_connect(objs->amod_volume_pfs_object,
                                        objs->acon_hops_pfs_rs_object->outs[0],
                                        objs->acon_hops_pfs_vol_object->in);

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    asnk_hops_connect(objs->asnk_hops_seps_vol_object,
                                      objs->acon_hops_seps_vol_object->outs[0]);

                    asnk_hops_connect(objs->asnk_hops_pfs_vol_object,
                                      objs->acon_hops_pfs_vol_object->outs[0]);

            // +------------------------------------------------------+
            // | Classify                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_classify_connect(objs->amod_classify_object,
                                          objs->acon_hops_seps_object->outs[1],
                                          objs->acon_tracks_sst_object->outs[1],
                                          objs->acon_categories_object->in);

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+  

                    asnk_categories_connect(objs->asnk_categories_object,
                                            objs->acon_categories_object->outs[0]);

        // +----------------------------------------------------------+
        // | Enable modules                                           |
        // +----------------------------------------------------------+  

            amod_mapping_enable(objs->amod_mapping_mics_object);
            amod_resample_enable(objs->amod_resample_mics_object);
            amod_stft_enable(objs->amod_stft_mics_object);

            if (cfgs->snk_pots_ssl_config->interface->type != interface_blackhole) {

                amod_ssl_enable(objs->amod_ssl_object);

            }

            if (cfgs->snk_tracks_sst_config->interface->type != interface_blackhole) {

                amod_ssl_enable(objs->amod_ssl_object);
                amod_sst_enable(objs->amod_sst_object);

            }

            if (cfgs->snk_hops_seps_vol_config->interface->type != interface_blackhole) {

                amod_ssl_enable(objs->amod_ssl_object);
                amod_sst_enable(objs->amod_sst_object);
                amod_noise_enable(objs->amod_noise_mics_object);
                amod_sss_enable(objs->amod_sss_object);
                amod_istft_enable(objs->amod_istft_seps_object);
                amod_resample_enable(objs->amod_resample_seps_object);
                amod_volume_enable(objs->amod_volume_seps_object);

            }

            if (cfgs->snk_hops_pfs_vol_config->interface->type != interface_blackhole) {

                amod_ssl_enable(objs->amod_ssl_object);
                amod_sst_enable(objs->amod_sst_object);
                amod_noise_enable(objs->amod_noise_mics_object);
                amod_sss_enable(objs->amod_sss_object);
                amod_istft_enable(objs->amod_istft_pfs_object);
                amod_resample_enable(objs->amod_resample_pfs_object);
                amod_volume_enable(objs->amod_volume_pfs_object);

            }

            if (cfgs->snk_categories_config->interface->type != interface_blackhole) {

                amod_ssl_enable(objs->amod_ssl_object);
                amod_sst_enable(objs->amod_sst_object);
                amod_noise_enable(objs->amod_noise_mics_object);
                amod_sss_enable(objs->amod_sss_object);
                amod_istft_enable(objs->amod_istft_seps_object);
                amod_classify_enable(objs->amod_classify_object);

            }

        return objs;

    }

    void aobjects_destroy(aobjects * objs) {

        unsigned int iSink;

        // +----------------------------------------------------------+
        // | Destroy                                                  |
        // +----------------------------------------------------------+

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    asrc_hops_destroy(objs->asrc_hops_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_mics_raw_object);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_mapping_destroy(objs->amod_mapping_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_mics_map_object);             

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_resample_destroy(objs->amod_resample_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_mics_rs_object);    

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_stft_destroy(objs->amod_stft_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_spectra_destroy(objs->acon_spectra_mics_object);   

            // +------------------------------------------------------+
            // | Noise                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_noise_destroy(objs->amod_noise_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_powers_destroy(objs->acon_powers_mics_object);  

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_ssl_destroy(objs->amod_ssl_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    asnk_pots_destroy(objs->asnk_pots_ssl_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_pots_destroy(objs->acon_pots_ssl_object);   

            // +------------------------------------------------------+
            // | Target                                               |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Injector                                         |
                // +--------------------------------------------------+  

                    ainj_targets_destroy(objs->ainj_targets_sst_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_targets_destroy(objs->acon_targets_sst_object);

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sst_destroy(objs->amod_sst_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    asnk_tracks_destroy(objs->asnk_tracks_sst_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_tracks_destroy(objs->acon_tracks_sst_object);  

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sss_destroy(objs->amod_sss_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_spectra_destroy(objs->acon_spectra_seps_object);
                    acon_spectra_destroy(objs->acon_spectra_pfs_object);                    

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+                      

                    amod_istft_destroy(objs->amod_istft_seps_object);
                    amod_istft_destroy(objs->amod_istft_pfs_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_seps_object);
                    acon_hops_destroy(objs->acon_hops_pfs_object);                     

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_resample_destroy(objs->amod_resample_seps_object);
                    amod_resample_destroy(objs->amod_resample_pfs_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_seps_rs_object);
                    acon_hops_destroy(objs->acon_hops_pfs_rs_object);                     

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_volume_destroy(objs->amod_volume_seps_object);
                    amod_volume_destroy(objs->amod_volume_pfs_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_seps_vol_object);
                    acon_hops_destroy(objs->acon_hops_pfs_vol_object);  

                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    asnk_hops_destroy(objs->asnk_hops_seps_vol_object);
                    asnk_hops_destroy(objs->asnk_hops_pfs_vol_object);

            // +------------------------------------------------------+
            // | Classify                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_classify_destroy(objs->amod_classify_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_categories_destroy(objs->acon_categories_object);
                
                // +--------------------------------------------------+
                // | Sink                                             |
                // +--------------------------------------------------+                      

                    asnk_categories_destroy(objs->asnk_categories_object);

        free((void *) objs);

    }