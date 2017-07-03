    
    #include "objects.h"

    objects * objects_construct(const configs * cfgs) {

        objects * objs;
        unsigned int iSink;

        objs = (objects *) malloc(sizeof(objects));

        objs->nMessages = 10;

        // +----------------------------------------------------------+
        // | Construct                                                |
        // +----------------------------------------------------------+

            // +------------------------------------------------------+
            // | Raw                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Source                                           |
                // +--------------------------------------------------+  

                    objs->asrc_hops_raw_object = asrc_hops_construct(cfgs->src_hops_raw_config, cfgs->msg_hops_raw_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_raw_object = amsg_hops_construct(objs->nMessages, cfgs->msg_hops_raw_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_raw_object_count = cfgs->snk_hops_raw_config_count;
                    objs->asnk_hops_raw_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_raw_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_raw_object_count; iSink++) {
                        objs->asnk_hops_raw_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_raw_configs[iSink], cfgs->msg_hops_raw_config);
                    }

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_mapping_object = amod_mapping_construct(cfgs->mod_mapping_config, cfgs->msg_hops_mapping_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_mapping_object = amsg_hops_construct(objs->nMessages, cfgs->msg_hops_mapping_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_mapping_object_count = cfgs->snk_hops_mapping_config_count;
                    objs->asnk_hops_mapping_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_mapping_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_mapping_object_count; iSink++) {
                        objs->asnk_hops_mapping_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_mapping_configs[iSink], cfgs->msg_hops_mapping_config);
                    }

            // +------------------------------------------------------+
            // | Resample                                             |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_resample_object = amod_resample_construct(cfgs->mod_resample_config, cfgs->msg_hops_mapping_config, cfgs->msg_hops_resample_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_resample_object = amsg_hops_construct(objs->nMessages, cfgs->msg_hops_resample_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_hops_resample_object_count = cfgs->snk_hops_resample_config_count;
                    objs->asnk_hops_resample_objects = (asnk_hops_obj **) malloc(sizeof(asnk_hops_obj *) * cfgs->snk_hops_resample_config_count);

                    for (iSink = 0; iSink < objs->asnk_hops_resample_object_count; iSink++) {
                        objs->asnk_hops_resample_objects[iSink] = asnk_hops_construct(cfgs->snk_hops_resample_configs[iSink], cfgs->msg_hops_resample_config);
                    }

            // +------------------------------------------------------+
            // | STFT                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_stft_object = amod_stft_construct(cfgs->mod_stft_config, cfgs->msg_hops_resample_config, cfgs->msg_spectra_stft_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_stft_object = amsg_spectra_construct(objs->nMessages, cfgs->msg_spectra_stft_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_spectra_stft_object_count = cfgs->snk_spectra_stft_config_count;
                    objs->asnk_spectra_stft_objects = (asnk_spectra_obj **) malloc(sizeof(asnk_spectra_obj *) * cfgs->snk_spectra_stft_config_count);

                    for (iSink = 0; iSink < objs->asnk_spectra_stft_object_count; iSink++) {
                        objs->asnk_spectra_stft_objects[iSink] = asnk_spectra_construct(cfgs->snk_spectra_stft_configs[iSink], cfgs->msg_spectra_stft_config);
                    }

            // +------------------------------------------------------+
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_ssl_object = amod_ssl_construct(cfgs->mod_ssl_config, cfgs->msg_spectra_stft_config, cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_pots_ssl_object = amsg_pots_construct(objs->nMessages, cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_pots_ssl_object_count = cfgs->snk_pots_ssl_config_count;
                    objs->asnk_pots_ssl_objects = (asnk_pots_obj **) malloc(sizeof(asnk_pots_obj *) * cfgs->snk_pots_ssl_config_count);

                    for (iSink = 0; iSink < objs->asnk_pots_ssl_object_count; iSink++) {
                        objs->asnk_pots_ssl_objects[iSink] = asnk_pots_construct(cfgs->snk_pots_ssl_configs[iSink], cfgs->msg_pots_ssl_config);
                    }

            // +------------------------------------------------------+
            // | SST                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sst_object = amod_sst_construct(cfgs->mod_sst_config, cfgs->mod_ssl_config, cfgs->msg_pots_ssl_config, cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_tracks_sst_object = amsg_tracks_construct(objs->nMessages, cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_tracks_sst_object_count = cfgs->snk_tracks_sst_config_count;
                    objs->asnk_tracks_sst_objects = (asnk_tracks_obj **) malloc(sizeof(asnk_tracks_obj *) * cfgs->snk_tracks_sst_config_count);

                    for (iSink = 0; iSink < objs->asnk_tracks_sst_object_count; iSink++) {
                        objs->asnk_tracks_sst_objects[iSink] = asnk_tracks_construct(cfgs->snk_tracks_sst_configs[iSink], cfgs->msg_tracks_sst_config);
                    }

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sss_object = amod_sss_construct(cfgs->mod_sss_config, cfgs->msg_spectra_sss_config, cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_sss_object = amsg_spectra_construct(objs->nMessages, cfgs->msg_spectra_sss_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_spectra_sss_object_count = cfgs->snk_spectra_sss_config_count;
                    objs->asnk_spectra_sss_objects = (asnk_spectra_obj **) malloc(sizeof(asnk_spectra_obj *) * cfgs->snk_spectra_sss_config_count);

                    for (iSink = 0; iSink < objs->asnk_spectra_sss_object_count; iSink++) {
                        objs->asnk_spectra_sss_objects[iSink] = asnk_spectra_construct(cfgs->snk_spectra_sss_configs[iSink], cfgs->msg_spectra_sss_config);
                    }

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_sspf_object = amod_sspf_construct(cfgs->mod_sspf_config, cfgs->msg_spectra_sspf_config, cfgs->msg_tracks_sst_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_sspf_object = amsg_spectra_construct(objs->nMessages, cfgs->msg_spectra_sspf_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_spectra_sspf_object_count = cfgs->snk_spectra_sspf_config_count;
                    objs->asnk_spectra_sspf_objects = (asnk_spectra_obj **) malloc(sizeof(asnk_spectra_obj *) * cfgs->snk_spectra_sspf_config_count);

                    for (iSink = 0; iSink < objs->asnk_spectra_sspf_object_count; iSink++) {
                        objs->asnk_spectra_sspf_objects[iSink] = asnk_spectra_construct(cfgs->snk_spectra_sspf_configs[iSink], cfgs->msg_spectra_sspf_config);
                    }                    

        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+  

            objs->acon_hops_raw_object = acon_hops_construct(objs->asnk_hops_raw_object_count+1, objs->nMessages, cfgs->msg_hops_raw_config);
            objs->acon_hops_mapping_object = acon_hops_construct(objs->asnk_hops_mapping_object_count+1, objs->nMessages, cfgs->msg_hops_mapping_config);
            objs->acon_hops_resample_object = acon_hops_construct(objs->asnk_hops_resample_object_count+1, objs->nMessages, cfgs->msg_hops_resample_config);
            objs->acon_spectra_stft_object = acon_spectra_construct(objs->asnk_spectra_stft_object_count+3, objs->nMessages, cfgs->msg_spectra_stft_config);
            objs->acon_pots_ssl_object = acon_pots_construct(objs->asnk_pots_ssl_object_count+1, objs->nMessages, cfgs->msg_pots_ssl_config);
            objs->acon_tracks_sst_object = acon_tracks_construct(objs->asnk_tracks_sst_object_count+2, objs->nMessages, cfgs->msg_tracks_sst_config);
            objs->acon_spectra_sss_object = acon_spectra_construct(objs->asnk_spectra_sss_object_count+1, objs->nMessages, cfgs->msg_spectra_sss_config);
            objs->acon_spectra_sspf_object = acon_spectra_construct(objs->asnk_spectra_sspf_object_count, objs->nMessages, cfgs->msg_spectra_sspf_config);

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
                                          objs->acon_hops_raw_object->outs[iSink+1]);

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
                                          objs->acon_hops_mapping_object->outs[iSink+1]);

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
                                          objs->acon_hops_resample_object->outs[iSink+1]);

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
                                             objs->acon_spectra_stft_object->outs[iSink+3]);

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
                                          objs->acon_pots_ssl_object->outs[iSink+1]);

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
                                            objs->acon_tracks_sst_object->outs[iSink+2]);

                    }

            // +------------------------------------------------------+
            // | SSS                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sss_connect(objs->amod_sss_object,
                                     objs->acon_spectra_stft_object->outs[1],
                                     objs->acon_tracks_sst_object->outs[0],
                                     objs->acon_spectra_sss_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_sss_object_count; iSink++) {

                        asnk_spectra_connect(objs->asnk_spectra_sss_objects[iSink],
                                             objs->acon_spectra_sss_object->outs[iSink+1]);

                    }

            // +------------------------------------------------------+
            // | SSPF                                                 |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_sspf_connect(objs->amod_sspf_object,
                                      objs->acon_spectra_stft_object->outs[2],
                                      objs->acon_spectra_sss_object->outs[0],
                                      objs->acon_tracks_sst_object->outs[1],
                                      objs->acon_spectra_sspf_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    for (iSink = 0; iSink < objs->asnk_spectra_sspf_object_count; iSink++) {

                        asnk_spectra_connect(objs->asnk_spectra_sspf_objects[iSink],
                                             objs->acon_spectra_sspf_object->outs[iSink]);

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

        free((void *) objs);

    }