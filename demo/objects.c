    
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

                    objs->src_hops_raw_object = src_hops_construct(cfgs->src_hops_raw_config, 
                                                                   cfgs->msg_hops_raw_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_raw_object = msg_hops_construct(cfgs->msg_hops_raw_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_hops_raw_object_count = cfgs->snk_hops_raw_config_count;
                    objs->snk_hops_raw_objects = (snk_hops_obj **) malloc(sizeof(snk_hops_obj *) * cfgs->snk_hops_raw_config_count);

                    for (iSink = 0; iSink < objs->snk_hops_raw_object_count; iSink++) {

                        objs->snk_hops_raw_objects[iSink] = snk_hops_construct(cfgs->snk_hops_raw_configs[iSink], 
                                                                               cfgs->msg_hops_raw_config);

                    }

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_mapping_object = mod_mapping_construct(cfgs->mod_mapping_config, 
                                                                     cfgs->msg_hops_mapping_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_mapping_object = msg_hops_construct(cfgs->msg_hops_mapping_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_hops_mapping_object_count = cfgs->snk_hops_mapping_config_count;
                    objs->snk_hops_mapping_objects = (snk_hops_obj **) malloc(sizeof(snk_hops_obj *) * cfgs->snk_hops_mapping_config_count);

                    for (iSink = 0; iSink < objs->snk_hops_mapping_object_count; iSink++) {

                        objs->snk_hops_mapping_objects[iSink] = snk_hops_construct(cfgs->snk_hops_mapping_configs[iSink], 
                                                                                   cfgs->msg_hops_mapping_config);

                    }

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_resample_object = mod_resample_construct(cfgs->mod_resample_config, 
                                                                       cfgs->msg_hops_mapping_config, 
                                                                       cfgs->msg_hops_resample_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_resample_object = msg_hops_construct(cfgs->msg_hops_resample_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_hops_resample_object_count = cfgs->snk_hops_resample_config_count;
                    objs->snk_hops_resample_objects = (snk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_resample_config_count);

                    for (iSink = 0; iSink < objs->snk_hops_resample_object_count; iSink++) {

                        objs->snk_hops_resample_objects[iSink] = snk_hops_construct(cfgs->snk_hops_resample_configs[iSink], 
                                                                                    cfgs->msg_hops_resample_config);

                    }

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_stft_object = mod_stft_construct(cfgs->mod_stft_config, 
                                                               cfgs->msg_hops_resample_config, 
                                                               cfgs->msg_spectra_stft_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_spectra_stft_object = msg_spectra_construct(cfgs->msg_spectra_stft_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_spectra_stft_object_count = cfgs->snk_spectra_stft_config_count;
                    objs->snk_spectra_stft_objects = (snk_spectra_obj **) malloc(sizeof(snk_spectra_obj *) * cfgs->snk_spectra_stft_config_count);

                    for (iSink = 0; iSink < objs->snk_spectra_stft_object_count; iSink++) {

                        objs->snk_spectra_stft_objects[iSink] = snk_spectra_construct(cfgs->snk_spectra_stft_configs[iSink], 
                                                                                      cfgs->msg_spectra_stft_config);

                    }

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_ssl_object = mod_ssl_construct(cfgs->mod_ssl_config, 
                                                             cfgs->msg_spectra_stft_config,
                                                             cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_pots_ssl_object = msg_pots_construct(cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_pots_ssl_object_count = cfgs->snk_pots_ssl_config_count;
                    objs->snk_pots_ssl_objects = (snk_pots_obj **) malloc(sizeof(snk_pots_obj *) * cfgs->snk_pots_ssl_config_count);

                    for (iSink = 0; iSink < objs->snk_pots_ssl_object_count; iSink++) {

                        objs->snk_pots_ssl_objects[iSink] = snk_pots_construct(cfgs->snk_pots_ssl_configs[iSink], 
                                                                               cfgs->msg_pots_ssl_config);

                    }

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_sst_object = mod_sst_construct(cfgs->mod_sst_config, 
                                                             cfgs->mod_ssl_config, 
                                                             cfgs->msg_pots_ssl_config, 
                                                             cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_tracks_sst_object = msg_tracks_construct(cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_tracks_sst_object_count = cfgs->snk_tracks_sst_config_count;
                    objs->snk_tracks_sst_objects = (snk_tracks_obj **) malloc(sizeof(snk_tracks_obj *) * cfgs->snk_tracks_sst_config_count);

                    for (iSink = 0; iSink < objs->snk_tracks_sst_object_count; iSink++) {

                        objs->snk_tracks_sst_objects[iSink] = snk_tracks_construct(cfgs->snk_tracks_sst_configs[iSink], 
                                                                                   cfgs->msg_tracks_sst_config);

                    }
/*
            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_sss_object = mod_sss_construct(cfgs->mod_sss_config, 
                                                             cfgs->msg_tracks_sst_config, 
                                                             cfgs->msg_spectra_sss_config, 
                                                             cfgs->msg_envs_sss_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_spectra_sss_object = msg_spectra_construct(cfgs->msg_spectra_sss_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_spectra_sss_object_count = cfgs->snk_spectra_sss_config_count;
                    objs->snk_spectra_sss_objects = (snk_spectra_obj **) malloc(sizeof(snk_spectra_obj *) * cfgs->snk_spectra_sss_config_count);

                    for (iSink = 0; iSink < objs->snk_spectra_sss_object_count; iSink++) {

                        objs->snk_spectra_sss_objects[iSink] = snk_spectra_construct(cfgs->snk_spectra_sss_configs[iSink], 
                                                                                     cfgs->msg_spectra_sss_config);

                    }

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_sspf_object = mod_sspf_construct(cfgs->mod_sspf_config, 
                                                              cfgs->msg_tracks_sst_config, 
                                                              cfgs->msg_spectra_sspf_config, 
                                                              cfgs->msg_envs_sss_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_spectra_sspf_object = msg_spectra_construct(cfgs->msg_spectra_sspf_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_spectra_sspf_object_count = cfgs->snk_spectra_sspf_config_count;
                    objs->snk_spectra_sspf_objects = (snk_spectra_obj **) malloc(sizeof(snk_spectra_obj *) * cfgs->snk_spectra_sspf_config_count);

                    for (iSink = 0; iSink < objs->snk_spectra_sspf_object_count; iSink++) {

                        objs->snk_spectra_sspf_objects[iSink] = snk_spectra_construct(cfgs->snk_spectra_sspf_configs[iSink], 
                                                                                      cfgs->msg_spectra_sspf_config);

                    }

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_istft_object = mod_istft_construct(cfgs->mod_istft_config, 
                                                                 cfgs->msg_spectra_sspf_config, 
                                                                 cfgs->msg_hops_istft_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_istft_object = msg_hops_construct(cfgs->msg_hops_istft_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_hops_istft_object_count = cfgs->snk_hops_istft_config_count;
                    objs->snk_hops_istft_objects = (snk_hops_obj **) malloc(sizeof(snk_hops_obj *) * cfgs->snk_hops_istft_config_count);

                    for (iSink = 0; iSink < objs->snk_hops_istft_object_count; iSink++) {

                        objs->snk_hops_istft_objects[iSink] = snk_hops_construct(cfgs->snk_hops_istft_configs[iSink], 
                                                                                 cfgs->msg_hops_istft_config);

                    }

            // +------------------------------------------------------+
            // | Gain                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_gain_object = mod_gain_construct(cfgs->mod_gain_config, 
                                                               cfgs->msg_hops_gain_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_gain_object = msg_hops_construct(cfgs->msg_hops_gain_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_hops_gain_object_count = cfgs->snk_hops_gain_config_count;
                    objs->snk_hops_gain_objects = (snk_hops_obj **) malloc(sizeof(snk_hops_obj *) * cfgs->snk_hops_gain_config_count);

                    for (iSink = 0; iSink < objs->snk_hops_gain_object_count; iSink++) {

                        objs->snk_hops_gain_objects[iSink] = snk_hops_construct(cfgs->snk_hops_gain_configs[iSink], 
                                                                                cfgs->msg_hops_gain_config);

                    }
*/
        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+  

            // Hops ....... Raw ........ (0): Mapping Hops
            //                  ........ (1): Sink 1
            //                  ........ (2): Sink 2
            //                                etc.
            //
            // Hops ....... Mapping .... (0): Resample Hops
            //                      .... (1): Sink 1
            //                      .... (2): Sink 2
            //                                etc.
            //
            // Hops ....... Resample ... (0): STFT Hops
            //                       ... (1): Sink 1
            //                       ... (2): Sink 2
            //                                etc.
            //
            // Spectra .... STFT ....... (0): SSL
            //                   ....... (1): SSS
            //                   ....... (2): Sink 1
            //                   ....... (3): Sink 2
            //                                etc.
            //
            // Pots ....... SSL ........ (0): SST
            //                  ........ (1): Sink 1
            //                  ........ (2): Sink 2
            //                                etc.
            //
            // Tracks ..... SST ........ (0): SSS
            //                  ........ (1): SSPF
            //                  ........ (2): Sink 1
            //                  ........ (3): Sink 2
            //                                etc.
            //
            // Spectra .... SSS ........ (0): SSPF
            //                  ........ (1): Sink 1
            //                  ........ (2): Sink 2
            //                                etc.
            //
            // Envs ....... SSS ........ (0): SSPF
            //
            // Spectra .... SSPF ....... (0): ISTFT
            //                   ....... (1): Sink 1
            //                   ....... (2): Sink 2
            //                                etc.
            //
            // Hops ....... ISTFT ...... (0): Gain
            //                    ...... (1): Sink 1
            //                    ...... (2): Sink 2
            //                                etc.
            //
            // Hops ....... Gain ....... (0): Sink 1
            //                   ....... (1): Sink 2
            //                                etc.

            objs->con_hops_raw_object = con_hops_construct(objs->snk_hops_raw_object_count + 1, 
                                                           cfgs->msg_hops_raw_config);

            objs->con_hops_mapping_object = con_hops_construct(objs->snk_hops_mapping_object_count + 1, 
                                                               cfgs->msg_hops_mapping_config);

            objs->con_hops_resample_object = con_hops_construct(objs->snk_hops_resample_object_count + 1, 
                                                                cfgs->msg_hops_resample_config);

            objs->con_spectra_stft_object = con_spectra_construct(objs->snk_spectra_stft_object_count + 1, 
                                                                  cfgs->msg_spectra_stft_config);

            objs->con_pots_ssl_object = con_pots_construct(objs->snk_pots_ssl_object_count + 1, 
                                                           cfgs->msg_pots_ssl_config);

            objs->con_tracks_sst_object = con_tracks_construct(objs->snk_tracks_sst_object_count + 0, 
                                                               cfgs->msg_tracks_sst_config);
/*
            objs->con_spectra_sss_object = con_spectra_construct(objs->snk_spectra_sss_object_count + 1, 
                                                                 cfgs->msg_spectra_sss_config);

            objs->con_envs_sss_object = con_envs_construct(1,
                                                           cfgs->msg_envs_sss_config);

            objs->con_spectra_sspf_object = con_spectra_construct(objs->snk_spectra_sspf_object_count + 1, 
                                                                  cfgs->msg_spectra_sspf_config);

            objs->con_hops_istft_object = con_hops_construct(objs->snk_hops_istft_object_count + 1,
                                                             cfgs->msg_hops_istft_config);

            objs->con_hops_gain_object = con_hops_construct(objs->snk_hops_gain_object_count,
                                                            cfgs->msg_hops_gain_config);
*/
            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    src_hops_connect(objs->src_hops_raw_object, 
                                     objs->con_hops_raw_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_raw_object_count; iSink++) {
                        
                        snk_hops_connect(objs->snk_hops_raw_objects[iSink], 
                                         objs->con_hops_raw_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_mapping_connect(objs->mod_mapping_object, 
                                        objs->con_hops_raw_object->outs[0], 
                                        objs->con_hops_mapping_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_mapping_object_count; iSink++) {

                        snk_hops_connect(objs->snk_hops_mapping_objects[iSink],
                                         objs->con_hops_mapping_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_resample_connect(objs->mod_resample_object, 
                                         objs->con_hops_mapping_object->outs[0], 
                                         objs->con_hops_resample_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_resample_object_count; iSink++) {

                        snk_hops_connect(objs->snk_hops_resample_objects[iSink],
                                         objs->con_hops_resample_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_stft_connect(objs->mod_stft_object, 
                                     objs->con_hops_resample_object->outs[0], 
                                     objs->con_spectra_stft_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_spectra_stft_object_count; iSink++) {

                        snk_spectra_connect(objs->snk_spectra_stft_objects[iSink],
                                            objs->con_spectra_stft_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_ssl_connect(objs->mod_ssl_object, 
                                    objs->con_spectra_stft_object->outs[0], 
                                    objs->con_pots_ssl_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_pots_ssl_object_count; iSink++) {

                        snk_pots_connect(objs->snk_pots_ssl_objects[iSink],
                                         objs->con_pots_ssl_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sst_connect(objs->mod_sst_object, 
                                    objs->con_pots_ssl_object->outs[0], 
                                    objs->con_tracks_sst_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_tracks_sst_object_count; iSink++) {

                        snk_tracks_connect(objs->snk_tracks_sst_objects[iSink],
                                           objs->con_tracks_sst_object->outs[iSink + 0]);

                    }
/*
            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sss_connect(objs->mod_sss_object,
                                    objs->con_spectra_stft_object->outs[1],
                                    objs->con_tracks_sst_object->outs[0],
                                    objs->con_spectra_sss_object->in,
                                    objs->con_envs_sss_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_spectra_sss_object_count; iSink++) {

                        snk_spectra_connect(objs->snk_spectra_sss_objects[iSink],
                                            objs->con_spectra_sss_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sspf_connect(objs->mod_sspf_object,
                                     objs->con_spectra_sss_object->outs[0],
                                     objs->con_envs_sss_object->outs[0],
                                     objs->con_tracks_sst_object->outs[1],
                                     objs->con_spectra_sspf_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_spectra_sspf_object_count; iSink++) {

                        snk_spectra_connect(objs->snk_spectra_sspf_objects[iSink],
                                            objs->con_spectra_sspf_object->outs[iSink + 1]);

                    }                    

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_istft_connect(objs->mod_istft_object,
                                      objs->con_spectra_sspf_object->outs[0],
                                      objs->con_hops_istft_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_istft_object_count; iSink++) {

                        snk_hops_connect(objs->snk_hops_istft_objects[iSink],
                                         objs->con_hops_istft_object->outs[iSink + 1]);

                    }      

            // +------------------------------------------------------+
            // | Gain                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_gain_connect(objs->mod_gain_object,
                                     objs->con_hops_istft_object->outs[0],
                                     objs->con_hops_gain_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_gain_object_count; iSink++) {

                        snk_hops_connect(objs->snk_hops_gain_objects[iSink],
                                         objs->con_hops_gain_object->outs[iSink]);

                    }  
*/
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

                    src_hops_destroy(objs->src_hops_raw_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_raw_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_raw_object_count; iSink++) {

                        snk_hops_destroy(objs->snk_hops_raw_objects[iSink]);

                    }

                    free((void *) objs->snk_hops_raw_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_raw_object);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_mapping_destroy(objs->mod_mapping_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_mapping_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_mapping_object_count; iSink++) {

                        snk_hops_destroy(objs->snk_hops_mapping_objects[iSink]);

                    }

                    free((void *) objs->snk_hops_mapping_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_mapping_object);             

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_resample_destroy(objs->mod_resample_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_resample_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_resample_object_count; iSink++) {

                        snk_hops_destroy(objs->snk_hops_resample_objects[iSink]);

                    }

                    free((void *) objs->snk_hops_resample_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_resample_object);    

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_stft_destroy(objs->mod_stft_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_spectra_destroy(objs->msg_spectra_stft_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_spectra_stft_object_count; iSink++) {

                        snk_spectra_destroy(objs->snk_spectra_stft_objects[iSink]);

                    }

                    free((void *) objs->snk_spectra_stft_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_spectra_destroy(objs->con_spectra_stft_object);   

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_ssl_destroy(objs->mod_ssl_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_pots_destroy(objs->msg_pots_ssl_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_pots_ssl_object_count; iSink++) {

                        snk_pots_destroy(objs->snk_pots_ssl_objects[iSink]);

                    }

                    free((void *) objs->snk_pots_ssl_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_pots_destroy(objs->con_pots_ssl_object);   

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sst_destroy(objs->mod_sst_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_tracks_destroy(objs->msg_tracks_sst_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_tracks_sst_object_count; iSink++) {

                        snk_tracks_destroy(objs->snk_tracks_sst_objects[iSink]);

                    }

                    free((void *) objs->snk_tracks_sst_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_tracks_destroy(objs->con_tracks_sst_object);   
/*
            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sss_destroy(objs->mod_sss_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_spectra_destroy(objs->msg_spectra_sss_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_spectra_sss_object_count; iSink++) {

                        snk_spectra_destroy(objs->snk_spectra_sss_objects[iSink]);

                    }

                    free((void *) objs->snk_spectra_sss_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_spectra_destroy(objs->con_spectra_sss_object);   
                    con_envs_destroy(objs->con_envs_sss_object);

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_sspf_destroy(objs->mod_sspf_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_spectra_destroy(objs->msg_spectra_sspf_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_spectra_sspf_object_count; iSink++) {

                        snk_spectra_destroy(objs->snk_spectra_sspf_objects[iSink]);

                    }

                    free((void *) objs->snk_spectra_sspf_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_spectra_destroy(objs->con_spectra_sspf_object);   

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_istft_destroy(objs->mod_istft_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_istft_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_istft_object_count; iSink++) {

                        snk_hops_destroy(objs->snk_hops_istft_objects[iSink]);

                    }

                    free((void *) objs->snk_hops_istft_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_istft_object);                       

            // +------------------------------------------------------+
            // | Gain                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_gain_destroy(objs->mod_gain_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_gain_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->snk_hops_gain_object_count; iSink++) {

                        snk_hops_destroy(objs->snk_hops_gain_objects[iSink]);

                    }

                    free((void *) objs->snk_hops_gain_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_hops_destroy(objs->con_hops_gain_object);                      
*/
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

                    objs->asrc_hops_raw_object = asrc_hops_construct(cfgs->src_hops_raw_config, 
                                                                     cfgs->msg_hops_raw_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_raw_object = amsg_hops_construct(objs->nMessages, 
                                                                     cfgs->msg_hops_raw_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_raw_object_count = cfgs->snk_hops_raw_config_count;
                    objs->asnk_hops_raw_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_raw_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_raw_object_count; iSink++) {

                        objs->asnk_hops_raw_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_raw_configs[iSink], 
                                                                                 cfgs->msg_hops_raw_config);

                    }

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_mapping_object = amod_mapping_construct(cfgs->mod_mapping_config, 
                                                                       cfgs->msg_hops_mapping_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_mapping_object = amsg_hops_construct(objs->nMessages, 
                                                                         cfgs->msg_hops_mapping_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_mapping_object_count = cfgs->snk_hops_mapping_config_count;
                    objs->asnk_hops_mapping_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_mapping_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_mapping_object_count; iSink++) {

                        objs->asnk_hops_mapping_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_mapping_configs[iSink], 
                                                                                     cfgs->msg_hops_mapping_config);

                    }

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_resample_object = amod_resample_construct(cfgs->mod_resample_config, 
                                                                         cfgs->msg_hops_mapping_config, 
                                                                         cfgs->msg_hops_resample_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_resample_object = amsg_hops_construct(objs->nMessages, 
                                                                          cfgs->msg_hops_resample_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_resample_object_count = cfgs->snk_hops_resample_config_count;
                    objs->asnk_hops_resample_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_resample_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_resample_object_count; iSink++) {

                        objs->asnk_hops_resample_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_resample_configs[iSink], 
                                                                                      cfgs->msg_hops_resample_config);

                    }

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_stft_object = amod_stft_construct(cfgs->mod_stft_config, 
                                                                 cfgs->msg_hops_resample_config, 
                                                                 cfgs->msg_spectra_stft_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_stft_object = amsg_spectra_construct(objs->nMessages, 
                                                                            cfgs->msg_spectra_stft_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_spectra_stft_object_count = cfgs->snk_spectra_stft_config_count;
                    objs->asnk_spectra_stft_objects = (asnk_spectra_obj **) malloc(sizeof(asnk_spectra_obj *) * cfgs->snk_spectra_stft_config_count);

                    for (iSink = 0; iSink < objs->asnk_spectra_stft_object_count; iSink++) {

                        objs->asnk_spectra_stft_objects[iSink] = asnk_spectra_construct(cfgs->snk_spectra_stft_configs[iSink], 
                                                                                        cfgs->msg_spectra_stft_config);

                    }

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_ssl_object = amod_ssl_construct(cfgs->mod_ssl_config, 
                                                               cfgs->msg_spectra_stft_config, 
                                                               cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_pots_ssl_object = amsg_pots_construct(objs->nMessages, 
                                                                     cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_pots_ssl_object_count = cfgs->snk_pots_ssl_config_count;
                    objs->asnk_pots_ssl_objects = (asnk_pots_obj **) malloc(sizeof(asnk_pots_obj *) * cfgs->snk_pots_ssl_config_count);

                    for (iSink = 0; iSink < objs->asnk_pots_ssl_object_count; iSink++) {

                        objs->asnk_pots_ssl_objects[iSink] = asnk_pots_construct(cfgs->snk_pots_ssl_configs[iSink], 
                                                                                 cfgs->msg_pots_ssl_config);

                    }

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sst_object = amod_sst_construct(cfgs->mod_sst_config, 
                                                               cfgs->mod_ssl_config, 
                                                               cfgs->msg_pots_ssl_config, 
                                                               cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_tracks_sst_object = amsg_tracks_construct(objs->nMessages, 
                                                                         cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_tracks_sst_object_count = cfgs->snk_tracks_sst_config_count;
                    objs->asnk_tracks_sst_objects = (asnk_tracks_obj **) malloc(sizeof(asnk_tracks_obj *) * cfgs->snk_tracks_sst_config_count);

                    for (iSink = 0; iSink < objs->asnk_tracks_sst_object_count; iSink++) {

                        objs->asnk_tracks_sst_objects[iSink] = asnk_tracks_construct(cfgs->snk_tracks_sst_configs[iSink], 
                                                                                     cfgs->msg_tracks_sst_config);

                    }
/*
            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sss_object = amod_sss_construct(cfgs->mod_sss_config, 
                                                               cfgs->msg_tracks_sst_config,
                                                               cfgs->msg_spectra_sss_config, 
                                                               cfgs->msg_envs_sss_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_sss_object = amsg_spectra_construct(objs->nMessages, 
                                                                           cfgs->msg_spectra_sss_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_spectra_sss_object_count = cfgs->snk_spectra_sss_config_count;
                    objs->asnk_spectra_sss_objects = (asnk_spectra_obj **) malloc(sizeof(asnk_spectra_obj *) * cfgs->snk_spectra_sss_config_count);

                    for (iSink = 0; iSink < objs->asnk_spectra_sss_object_count; iSink++) {

                        objs->asnk_spectra_sss_objects[iSink] = asnk_spectra_construct(cfgs->snk_spectra_sss_configs[iSink], 
                                                                                       cfgs->msg_spectra_sss_config);

                    }

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sspf_object = amod_sspf_construct(cfgs->mod_sspf_config, 
                                                                 cfgs->msg_tracks_sst_config,
                                                                 cfgs->msg_spectra_sspf_config, 
                                                                 cfgs->msg_envs_sss_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_sspf_object = amsg_spectra_construct(objs->nMessages, 
                                                                            cfgs->msg_spectra_sspf_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_spectra_sspf_object_count = cfgs->snk_spectra_sspf_config_count;
                    objs->asnk_spectra_sspf_objects = (asnk_spectra_obj **) malloc(sizeof(asnk_spectra_obj *) * cfgs->snk_spectra_sspf_config_count);

                    for (iSink = 0; iSink < objs->asnk_spectra_sspf_object_count; iSink++) {

                        objs->asnk_spectra_sspf_objects[iSink] = asnk_spectra_construct(cfgs->snk_spectra_sspf_configs[iSink], 
                                                                                        cfgs->msg_spectra_sspf_config);

                    }                    


            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_istft_object = amod_istft_construct(cfgs->mod_istft_config, 
                                                                   cfgs->msg_spectra_sspf_config, 
                                                                   cfgs->msg_hops_istft_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_istft_object = amsg_hops_construct(objs->nMessages, 
                                                                       cfgs->msg_hops_istft_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_istft_object_count = cfgs->snk_hops_istft_config_count;
                    objs->asnk_hops_istft_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_istft_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_istft_object_count; iSink++) {

                        objs->asnk_hops_istft_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_istft_configs[iSink], 
                                                                                   cfgs->msg_hops_istft_config);

                    }                    

            // +------------------------------------------------------+
            // | Gain                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_gain_object = amod_gain_construct(cfgs->mod_gain_config, 
                                                                 cfgs->msg_hops_gain_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_gain_object = amsg_hops_construct(objs->nMessages, 
                                                                      cfgs->msg_hops_gain_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_gain_object_count = cfgs->snk_hops_gain_config_count;
                    objs->asnk_hops_gain_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_gain_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_gain_object_count; iSink++) {

                        objs->asnk_hops_gain_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_gain_configs[iSink], 
                                                                                  cfgs->msg_hops_gain_config);

                    }      
*/
        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+  

            // Hops ....... Raw ........ (0): Mapping Hops
            //                  ........ (1): Sink 1
            //                  ........ (2): Sink 2
            //                                etc.
            //
            // Hops ....... Mapping .... (0): Resample Hops
            //                      .... (1): Sink 1
            //                      .... (2): Sink 2
            //                                etc.
            //
            // Hops ....... Resample ... (0): STFT Hops
            //                       ... (1): Sink 1
            //                       ... (2): Sink 2
            //                                etc.
            //
            // Spectra .... STFT ....... (0): SSL
            //                   ....... (1): SSS
            //                   ....... (2): Sink 1
            //                   ....... (3): Sink 2
            //                                etc.
            //
            // Pots ....... SSL ........ (0): SST
            //                  ........ (1): Sink 1
            //                  ........ (2): Sink 2
            //                                etc.
            //
            // Tracks ..... SST ........ (0): SSS
            //                  ........ (1): SSPF
            //                  ........ (2): Sink 1
            //                  ........ (3): Sink 2
            //                                etc.
            //
            // Spectra .... SSS ........ (0): SSPF
            //                  ........ (1): Sink 1
            //                  ........ (2): Sink 2
            //                                etc.
            //
            // Envs ....... SSS ........ (0): SSPF
            //
            // Spectra .... SSPF ....... (0): ISTFT
            //                   ....... (1): Sink 1
            //                   ....... (2): Sink 2
            //                                etc.
            //
            // Hops ...... ISTFT ....... (0): Gain
            //                   ....... (1): Sink 1
            //                   ....... (2): Sink 2
            //                                etc.
            //
            // Hops ....... Gain ....... (0): Sink 1
            //                   ....... (1): Sink 2
            //                                etc.

            objs->acon_hops_raw_object = acon_hops_construct(objs->asnk_hops_raw_object_count + 1, 
                                                             objs->nMessages, 
                                                             cfgs->msg_hops_raw_config);

            objs->acon_hops_mapping_object = acon_hops_construct(objs->asnk_hops_mapping_object_count + 1, 
                                                                 objs->nMessages,
                                                                 cfgs->msg_hops_mapping_config);

            objs->acon_hops_resample_object = acon_hops_construct(objs->asnk_hops_resample_object_count + 1, 
                                                                  objs->nMessages, 
                                                                  cfgs->msg_hops_resample_config);

            objs->acon_spectra_stft_object = acon_spectra_construct(objs->asnk_spectra_stft_object_count + 1, 
                                                                    objs->nMessages,
                                                                    cfgs->msg_spectra_stft_config);

            objs->acon_pots_ssl_object = acon_pots_construct(objs->asnk_pots_ssl_object_count + 1, 
                                                             objs->nMessages,
                                                             cfgs->msg_pots_ssl_config);

            objs->acon_tracks_sst_object = acon_tracks_construct(objs->asnk_tracks_sst_object_count + 0, 
                                                                 objs->nMessages, 
                                                                 cfgs->msg_tracks_sst_config);
/*
            objs->acon_spectra_sss_object = acon_spectra_construct(objs->asnk_spectra_sss_object_count + 1, 
                                                                   objs->nMessages, 
                                                                   cfgs->msg_spectra_sss_config);

            objs->acon_envs_sss_object = acon_envs_construct(1,
                                                             objs->nMessages,
                                                             cfgs->msg_envs_sss_config);

            objs->acon_spectra_sspf_object = acon_spectra_construct(objs->asnk_spectra_sspf_object_count + 1, 
                                                                    objs->nMessages, 
                                                                    cfgs->msg_spectra_sspf_config);

            objs->acon_hops_istft_object = acon_hops_construct(objs->asnk_hops_istft_object_count + 1,
                                                               objs->nMessages,
                                                               cfgs->msg_hops_istft_config);

            objs->acon_hops_gain_object = acon_hops_construct(objs->asnk_hops_gain_object_count,
                                                              objs->nMessages,
                                                              cfgs->msg_hops_gain_config);
*/
            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    asrc_hops_connect(objs->asrc_hops_raw_object, 
                                      objs->acon_hops_raw_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_raw_object_count; iSink++) {
                        
                        asnk_hops_connect(objs->asnk_hops_raw_objects[iSink], 
                                          objs->acon_hops_raw_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_mapping_connect(objs->amod_mapping_object, 
                                         objs->acon_hops_raw_object->outs[0], 
                                         objs->acon_hops_mapping_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_mapping_object_count; iSink++) {

                        asnk_hops_connect(objs->asnk_hops_mapping_objects[iSink],
                                          objs->acon_hops_mapping_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_resample_connect(objs->amod_resample_object, 
                                          objs->acon_hops_mapping_object->outs[0], 
                                          objs->acon_hops_resample_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_resample_object_count; iSink++) {

                        asnk_hops_connect(objs->asnk_hops_resample_objects[iSink],
                                          objs->acon_hops_resample_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_stft_connect(objs->amod_stft_object, 
                                      objs->acon_hops_resample_object->outs[0], 
                                      objs->acon_spectra_stft_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_stft_object_count; iSink++) {

                        asnk_spectra_connect(objs->asnk_spectra_stft_objects[iSink],
                                             objs->acon_spectra_stft_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_ssl_connect(objs->amod_ssl_object, 
                                     objs->acon_spectra_stft_object->outs[0], 
                                     objs->acon_pots_ssl_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_pots_ssl_object_count; iSink++) {

                        asnk_pots_connect(objs->asnk_pots_ssl_objects[iSink],
                                          objs->acon_pots_ssl_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sst_connect(objs->amod_sst_object, 
                                     objs->acon_pots_ssl_object->outs[0], 
                                     objs->acon_tracks_sst_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_tracks_sst_object_count; iSink++) {

                        asnk_tracks_connect(objs->asnk_tracks_sst_objects[iSink],
                                            objs->acon_tracks_sst_object->outs[iSink + 0]);

                    }
/*
            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sss_connect(objs->amod_sss_object,
                                     objs->acon_spectra_stft_object->outs[1],
                                     objs->acon_tracks_sst_object->outs[0],
                                     objs->acon_spectra_sss_object->in,
                                     objs->acon_envs_sss_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_sss_object_count; iSink++) {

                        asnk_spectra_connect(objs->asnk_spectra_sss_objects[iSink],
                                             objs->acon_spectra_sss_object->outs[iSink + 1]);

                    }

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sspf_connect(objs->amod_sspf_object,
                                      objs->acon_spectra_sss_object->outs[0],
                                      objs->acon_envs_sss_object->outs[0],
                                      objs->acon_tracks_sst_object->outs[1],
                                      objs->acon_spectra_sspf_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_sspf_object_count; iSink++) {

                        asnk_spectra_connect(objs->asnk_spectra_sspf_objects[iSink],
                                             objs->acon_spectra_sspf_object->outs[iSink + 1]);

                    }           

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_istft_connect(objs->amod_istft_object,
                                       objs->acon_spectra_sspf_object->outs[0],
                                       objs->acon_hops_istft_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_istft_object_count; iSink++) {

                        asnk_hops_connect(objs->asnk_hops_istft_objects[iSink],
                                          objs->acon_hops_istft_object->outs[iSink + 1]);

                    }    

            // +------------------------------------------------------+
            // | Gain                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_gain_connect(objs->amod_gain_object,
                                      objs->acon_hops_istft_object->outs[0],
                                      objs->acon_hops_gain_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_gain_object_count; iSink++) {

                        asnk_hops_connect(objs->asnk_hops_gain_objects[iSink],
                                          objs->acon_hops_gain_object->outs[iSink]);

                    }    
*/
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

                    asrc_hops_destroy(objs->asrc_hops_raw_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_raw_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_raw_object_count; iSink++) {

                        asnk_hops_destroy(objs->asnk_hops_raw_objects[iSink]);

                    }

                    free((void *) objs->asnk_hops_raw_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_raw_object);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_mapping_destroy(objs->amod_mapping_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_mapping_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_mapping_object_count; iSink++) {

                        asnk_hops_destroy(objs->asnk_hops_mapping_objects[iSink]);

                    }

                    free((void *) objs->asnk_hops_mapping_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_mapping_object);             

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_resample_destroy(objs->amod_resample_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_resample_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_resample_object_count; iSink++) {

                        asnk_hops_destroy(objs->asnk_hops_resample_objects[iSink]);

                    }

                    free((void *) objs->asnk_hops_resample_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_resample_object);    

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_stft_destroy(objs->amod_stft_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_spectra_destroy(objs->amsg_spectra_stft_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_stft_object_count; iSink++) {

                        asnk_spectra_destroy(objs->asnk_spectra_stft_objects[iSink]);

                    }

                    free((void *) objs->asnk_spectra_stft_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_spectra_destroy(objs->acon_spectra_stft_object);   

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_ssl_destroy(objs->amod_ssl_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_pots_destroy(objs->amsg_pots_ssl_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_pots_ssl_object_count; iSink++) {

                        asnk_pots_destroy(objs->asnk_pots_ssl_objects[iSink]);

                    }

                    free((void *) objs->asnk_pots_ssl_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_pots_destroy(objs->acon_pots_ssl_object);   

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sst_destroy(objs->amod_sst_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_tracks_destroy(objs->amsg_tracks_sst_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_tracks_sst_object_count; iSink++) {

                        asnk_tracks_destroy(objs->asnk_tracks_sst_objects[iSink]);

                    }

                    free((void *) objs->asnk_tracks_sst_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_tracks_destroy(objs->acon_tracks_sst_object);   
/*
            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sss_destroy(objs->amod_sss_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_spectra_destroy(objs->amsg_spectra_sss_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_sss_object_count; iSink++) {

                        asnk_spectra_destroy(objs->asnk_spectra_sss_objects[iSink]);

                    }

                    free((void *) objs->asnk_spectra_sss_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_spectra_destroy(objs->acon_spectra_sss_object);   
                    acon_envs_destroy(objs->acon_envs_sss_object);

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sspf_destroy(objs->amod_sspf_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_spectra_destroy(objs->amsg_spectra_sspf_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_sspf_object_count; iSink++) {

                        asnk_spectra_destroy(objs->asnk_spectra_sspf_objects[iSink]);

                    }

                    free((void *) objs->asnk_spectra_sspf_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_spectra_destroy(objs->acon_spectra_sspf_object);   

            // +------------------------------------------------------+
            // | ISTFT                                                |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_istft_destroy(objs->amod_istft_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_istft_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_istft_object_count; iSink++) {

                        asnk_hops_destroy(objs->asnk_hops_istft_objects[iSink]);

                    }

                    free((void *) objs->asnk_hops_istft_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_istft_object);  

            // +------------------------------------------------------+
            // | Gain                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_gain_destroy(objs->amod_gain_object);
                    
                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_gain_object);
                    
                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_hops_gain_object_count; iSink++) {

                        asnk_hops_destroy(objs->asnk_hops_gain_objects[iSink]);

                    }

                    free((void *) objs->asnk_hops_gain_objects);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_hops_destroy(objs->acon_hops_gain_object);  
*/
        free((void *) objs);

    }