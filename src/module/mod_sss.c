    
    #include "mod_sss.h"

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_sss_obj * obj;
        
        obj = (mod_sss_obj *) malloc(sizeof(mod_sss_obj));

        obj->nSeps = msg_tracks_config->nTracks;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->mode_sep = mod_sss_config->mode_sep;
        obj->mode_pf = mod_sss_config->mode_pf;

        obj->beampatterns_mics = directivity_beampattern_mics(mod_sss_config->mics, 
                                                              mod_sss_config->nThetas);

        obj->beampatterns_spatialfilter = directivity_beampattern_spatialfilter(mod_sss_config->spatialfilter, 
                                                                                mod_sss_config->nThetas);

        obj->steers = steers_construct_zero(msg_spectra_config->halfFrameSize, 
                                            msg_tracks_config->nTracks, 
                                            msg_spectra_config->nChannels);

        obj->gains = gains_construct_zero(msg_tracks_config->nTracks,
                                          msg_spectra_config->nChannels);

        obj->masks = masks_construct_zero(msg_tracks_config->nTracks, 
                                          msg_spectra_config->nChannels);

        obj->track2gain = track2gain_construct_zero(msg_tracks_config->nTracks,
                                                    msg_spectra_config->nChannels,
                                                    mod_sss_config->mics->direction,
                                                    mod_sss_config->spatialfilter->direction);

        obj->gain2mask = gain2mask_construct_zero(msg_tracks_config->nTracks,
                                                  msg_spectra_config->nChannels,
                                                  mod_sss_config->gainMin);

        obj->track2steer = track2steer_construct_zero(msg_tracks_config->nTracks, 
                                                      msg_spectra_config->nChannels, 
                                                      msg_spectra_config->halfFrameSize, 
                                                      mod_sss_config->soundspeed->mu,
                                                      mod_sss_config->samplerate->mu,
                                                      mod_sss_config->mics->mu);

        switch(obj->mode_sep) {

            case 'd':

                obj->steer2demixing_ds = steer2demixing_ds_construct_zero(msg_tracks_config->nTracks, 
                                                                          msg_spectra_config->nChannels, 
                                                                          msg_spectra_config->halfFrameSize, 
                                                                          mod_sss_config->epsilon);
                obj->steer2demixing_gss = (steer2demixing_gss_obj *) NULL;
                obj->steer2demixing_mvdr = (steer2demixing_mvdr_obj *) NULL;

                break;

            break;

            case 'g':

                printf("GSS not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            case 'm':

                printf("MVDR not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            default:

                printf("Invalid separation method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        switch(obj->mode_pf) {

            case 'm':

                //printf("Multiple source post-filtering.\n");
                //exit(EXIT_FAILURE);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->demixingsPrev = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                      msg_tracks_config->nTracks, 
                                                      msg_spectra_config->nChannels);

        obj->demixingsNow = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                     msg_tracks_config->nTracks, 
                                                     msg_spectra_config->nChannels);

        obj->demixing2freq = demixing2freq_construct_zero(msg_tracks_config->nTracks,
                                                          msg_spectra_config->nChannels,
                                                          msg_spectra_config->halfFrameSize);


        return obj;

    }

    void mod_sss_destroy(mod_sss_obj * obj) {

        beampatterns_destroy(obj->beampatterns_mics);
        beampatterns_destroy(obj->beampatterns_spatialfilter);
        steers_destroy(obj->steers);
        gains_destroy(obj->gains);
        masks_destroy(obj->masks);
        track2gain_destroy(obj->track2gain);
        gain2mask_destroy(obj->gain2mask);
        track2steer_destroy(obj->track2steer);

        if (obj->steer2demixing_ds != NULL) {
            steer2demixing_ds_destroy(obj->steer2demixing_ds);
        }
        if (obj->steer2demixing_gss != NULL) {
            steer2demixing_gss_destroy(obj->steer2demixing_gss);
        }
        if (obj->steer2demixing_mvdr != NULL) {
            steer2demixing_mvdr_destroy(obj->steer2demixing_mvdr);
        }

        demixings_destroy(obj->demixingsPrev);
        demixings_destroy(obj->demixingsNow);
        demixing2freq_destroy(obj->demixing2freq);

        free((void *) obj);

    }

    int mod_sss_process(mod_sss_obj * obj) {

        int rtnValue1;
        int rtnValue2;
        int rtnValue;

        switch(obj->mode_sep) {

            case 'd':

                rtnValue1 = mod_sss_process_dds(obj);

            break;

            case 'g':

                rtnValue1 = mod_sss_process_dgss(obj);

            break;

            case 'm':

                rtnValue1 = mod_sss_process_dmvdr(obj);

            break;

            default:

                printf("Invalid separation method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        switch(obj->mode_pf) {

            case 'm':

                rtnValue2 = mod_sss_process_mspf(obj);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }        

        if (rtnValue1 != rtnValue2) {
            printf("Return value mismatch.\n");
            exit(EXIT_FAILURE);
        }
        else {
            rtnValue = rtnValue1;
        }

        return rtnValue;

    }

    int mod_sss_process_dds(mod_sss_obj * obj) {

        int rtnValue;

        if (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in2)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            track2gain_process(obj->track2gain, 
                               obj->beampatterns_mics, 
                               obj->beampatterns_spatialfilter, 
                               obj->in2->tracks,
                               obj->gains);

            gain2mask_process(obj->gain2mask, 
                              obj->gains, 
                              obj->masks);

            track2steer_process(obj->track2steer, 
                                obj->in2->tracks,
                                obj->gains,
                                obj->masks,
                                obj->steers);

            demixings_copy(obj->demixingsPrev, 
                           obj->demixingsNow);

            steer2demixing_ds_process(obj->steer2demixing_ds, 
                                      obj->in2->tracks,
                                      obj->steers, 
                                      obj->masks, 
                                      obj->demixingsNow);

            demixing2freq_process(obj->demixing2freq, 
                                  obj->in2->tracks,
                                  obj->demixingsNow, 
                                  obj->masks, 
                                  obj->in1->freqs, 
                                  obj->out1->freqs);

            freqs_zero(obj->out2->freqs);

            obj->out1->timeStamp = obj->in1->timeStamp;
            obj->out2->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);
            msg_spectra_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;        

    }

    int mod_sss_process_dgss(mod_sss_obj * obj) {

        int rtnValue;

        if (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in2)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            track2gain_process(obj->track2gain, 
                               obj->beampatterns_mics, 
                               obj->beampatterns_spatialfilter, 
                               obj->in2->tracks,
                               obj->gains);

            gain2mask_process(obj->gain2mask, 
                              obj->gains, 
                              obj->masks);

            track2steer_process(obj->track2steer, 
                                obj->in2->tracks,
                                obj->gains,
                                obj->masks,
                                obj->steers);

            demixings_copy(obj->demixingsPrev,
                           obj->demixingsNow);

            demixing2freq_process(obj->demixing2freq, 
                                  obj->in2->tracks,
                                  obj->demixingsNow, 
                                  obj->masks, 
                                  obj->in1->freqs, 
                                  obj->out1->freqs);        

        }
        else {

            msg_spectra_zero(obj->out1);
            msg_spectra_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;       

    }

    int mod_sss_process_dmvdr(mod_sss_obj * obj) {

        int rtnValue;

        if (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in2)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            track2gain_process(obj->track2gain, 
                               obj->beampatterns_mics, 
                               obj->beampatterns_spatialfilter, 
                               obj->in2->tracks,
                               obj->gains);

            gain2mask_process(obj->gain2mask, 
                              obj->gains, 
                              obj->masks);

            track2steer_process(obj->track2steer, 
                                obj->in2->tracks,
                                obj->gains,
                                obj->masks,
                                obj->steers);

        }
        else {

            msg_spectra_zero(obj->out1);
            msg_spectra_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;    

    }

    int mod_sss_process_mspf(mod_sss_obj * obj) {

        // Empty

    }

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out1, msg_spectra_obj * out2) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out1 = out1;
        obj->out2 = out2;

    }

    void mod_sss_disconnect(mod_sss_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out1 = (msg_spectra_obj *) NULL;
        obj->out2 = (msg_spectra_obj *) NULL;

    }

    mod_sss_cfg * mod_sss_cfg_construct(void) {

        mod_sss_cfg * cfg;

        cfg = (mod_sss_cfg *) malloc(sizeof(mod_sss_cfg));

        cfg->mode_sep = 0x00;
        cfg->mode_pf = 0x00;

        cfg->nThetas = 0;
        cfg->gainMin = 0.0f;

        cfg->mics = (mics_obj *) NULL;
        cfg->samplerate = (samplerate_obj *) NULL;
        cfg->soundspeed = (soundspeed_obj *) NULL;
        cfg->spatialfilter = (spatialfilter_obj *) NULL;  

        return cfg;

    }

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg) {

        if (cfg->mics != NULL) {
            mics_destroy(cfg->mics);
        }

        if (cfg->samplerate != NULL) {
            samplerate_destroy(cfg->samplerate);
        }

        if (cfg->soundspeed != NULL) {
            soundspeed_destroy(cfg->soundspeed);
        }

        if (cfg->spatialfilter != NULL) {
            spatialfilter_destroy(cfg->spatialfilter);
        }

        free((void *) cfg);

    }

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg) {
        
        // Empty

    }