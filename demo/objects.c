    
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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_mics_raw_object = msg_hops_construct(cfgs->msg_hops_mics_raw_config);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->mod_mapping_mics_object = mod_mapping_construct(cfgs->mod_mapping_mics_config, 
                                                                          cfgs->msg_hops_mics_map_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_mics_map_object = msg_hops_construct(cfgs->msg_hops_mics_map_config);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_hops_mics_rs_object = msg_hops_construct(cfgs->msg_hops_mics_rs_config);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_spectra_mics_object = msg_spectra_construct(cfgs->msg_spectra_mics_config);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->msg_pots_ssl_object = msg_pots_construct(cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->snk_pots_ssl_object = snk_pots_construct(cfgs->snk_pots_ssl_config, 
                                                                   cfgs->msg_pots_ssl_config);


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

                    objs->snk_tracks_sst_object = snk_tracks_construct(cfgs->snk_tracks_sst_config, 
                                                                       cfgs->msg_tracks_sst_config);

        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+  

            objs->con_hops_mics_raw_object = con_hops_construct(1, cfgs->msg_hops_mics_raw_config);

            objs->con_hops_mics_map_object = con_hops_construct(1, cfgs->msg_hops_mics_map_config);

            objs->con_hops_mics_rs_object = con_hops_construct(1, cfgs->msg_hops_mics_rs_config);

            objs->con_spectra_mics_object = con_spectra_construct(1, cfgs->msg_spectra_mics_config);

            objs->con_pots_ssl_object = con_pots_construct(2, cfgs->msg_pots_ssl_config);

            objs->con_tracks_sst_object = con_tracks_construct(1, cfgs->msg_tracks_sst_config);

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
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    mod_ssl_connect(objs->mod_ssl_object, 
                                    objs->con_spectra_mics_object->outs[0], 
                                    objs->con_pots_ssl_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    snk_pots_connect(objs->snk_pots_ssl_object,
                                     objs->con_pots_ssl_object->outs[1]);

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

                    snk_tracks_connect(objs->snk_tracks_sst_object,
                                       objs->con_tracks_sst_object->outs[0]);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_mics_raw_object);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_mics_map_object);                  

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_hops_destroy(objs->msg_hops_mics_rs_object);
                    
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
                // | Message                                          |
                // +--------------------------------------------------+  

                    msg_spectra_destroy(objs->msg_spectra_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_spectra_destroy(objs->con_spectra_mics_object);   

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

                    snk_pots_destroy(objs->snk_pots_ssl_object);

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

                    snk_tracks_destroy(objs->snk_tracks_sst_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    con_tracks_destroy(objs->con_tracks_sst_object); 

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_mics_raw_object = amsg_hops_construct(objs->nMessages, 
                                                                          cfgs->msg_hops_mics_raw_config);

            // +------------------------------------------------------+
            // | Mapping                                              |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    objs->amod_mapping_mics_object = amod_mapping_construct(cfgs->mod_mapping_mics_config, 
                                                                            cfgs->msg_hops_mics_map_config);

                // +--------------------------------------------------+
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_mics_map_object = amsg_hops_construct(objs->nMessages, 
                                                                          cfgs->msg_hops_mics_map_config);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_hops_mics_rs_object = amsg_hops_construct(objs->nMessages, 
                                                                         cfgs->msg_hops_mics_rs_config);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_spectra_mics_object = amsg_spectra_construct(objs->nMessages, 
                                                                            cfgs->msg_spectra_mics_config);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    objs->amsg_pots_ssl_object = amsg_pots_construct(objs->nMessages, 
                                                                     cfgs->msg_pots_ssl_config);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    objs->asnk_pots_ssl_object = asnk_pots_construct(cfgs->snk_pots_ssl_config, 
                                                                     cfgs->msg_pots_ssl_config);

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

                    objs->asnk_tracks_sst_object = asnk_tracks_construct(cfgs->snk_tracks_sst_config, 
                                                                         cfgs->msg_tracks_sst_config);

        // +----------------------------------------------------------+
        // | Connect                                                  |
        // +----------------------------------------------------------+  

            objs->acon_hops_mics_raw_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_mics_raw_config);

            objs->acon_hops_mics_map_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_mics_map_config);

            objs->acon_hops_mics_rs_object = acon_hops_construct(1, objs->nMessages, cfgs->msg_hops_mics_rs_config);

            objs->acon_spectra_mics_object = acon_spectra_construct(1, objs->nMessages, cfgs->msg_spectra_mics_config);

            objs->acon_pots_ssl_object = acon_pots_construct(2, objs->nMessages, cfgs->msg_pots_ssl_config);

            objs->acon_tracks_sst_object = acon_tracks_construct(1, objs->nMessages, cfgs->msg_tracks_sst_config);

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
            // | SSL                                                  |
            // +------------------------------------------------------+  

                // +--------------------------------------------------+
                // | Module                                           |
                // +--------------------------------------------------+  

                    amod_ssl_connect(objs->amod_ssl_object, 
                                     objs->acon_spectra_mics_object->outs[0], 
                                     objs->acon_pots_ssl_object->in);

                // +--------------------------------------------------+
                // | Sinks                                            |
                // +--------------------------------------------------+  

                    asnk_pots_connect(objs->asnk_pots_ssl_object,
                                      objs->acon_pots_ssl_object->outs[1]);

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

                    asnk_tracks_connect(objs->asnk_tracks_sst_object,
                                        objs->acon_tracks_sst_object->outs[0]);

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
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_mics_raw_object);
                    
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
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_mics_map_object);
                    
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
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_hops_destroy(objs->amsg_hops_mics_rs_object);
                    
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
                // | Message                                          |
                // +--------------------------------------------------+  

                    amsg_spectra_destroy(objs->amsg_spectra_mics_object);
                    
                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_spectra_destroy(objs->acon_spectra_mics_object);   

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

                    asnk_pots_destroy(objs->asnk_pots_ssl_object);

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

                    asnk_tracks_destroy(objs->asnk_tracks_sst_object);

                // +--------------------------------------------------+
                // | Connector                                        |
                // +--------------------------------------------------+  

                    acon_tracks_destroy(objs->acon_tracks_sst_object);  

        free((void *) objs);

    }