    
    #include "mod_sss.h"

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_sss_obj * obj;
        
        obj = (mod_sss_obj *) malloc(sizeof(mod_sss_obj));

        obj->nSeps = msg_tracks_config->nTracks;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->mode_sep = mod_sss_config->mode_sep;
        obj->mode_pf = mod_sss_config->mode_pf;

        switch(obj->mode_sep) {

            case 'd':

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

                obj->tracksPrev = tracks_construct_zero(msg_tracks_config->nTracks);

                obj->tracksNow = tracks_construct_zero(msg_tracks_config->nTracks);

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

                obj->steer2demixing_ds = steer2demixing_ds_construct_zero(msg_tracks_config->nTracks, 
                                                                          msg_spectra_config->nChannels, 
                                                                          msg_spectra_config->halfFrameSize, 
                                                                          mod_sss_config->epsilon);

                obj->steer2demixing_gss = (steer2demixing_gss_obj *) NULL;
                obj->steer2demixing_mvdr = (steer2demixing_mvdr_obj *) NULL;

                obj->demixingsPrev = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                              msg_tracks_config->nTracks, 
                                                              msg_spectra_config->nChannels);

                obj->demixingsNow = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                             msg_tracks_config->nTracks, 
                                                             msg_spectra_config->nChannels);

                obj->demixing2freq = demixing2freq_construct_zero(msg_tracks_config->nTracks,
                                                                  msg_spectra_config->nChannels,
                                                                  msg_spectra_config->halfFrameSize);

            break;

            case 'g':

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

                obj->tracksPrev = tracks_construct_zero(msg_tracks_config->nTracks);

                obj->tracksNow = tracks_construct_zero(msg_tracks_config->nTracks);

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

                obj->steer2demixing_ds = (steer2demixing_ds_obj *) NULL;
                obj->steer2demixing_gss = steer2demixing_gss_construct_zero(msg_tracks_config->nTracks, 
                                                                            msg_spectra_config->nChannels, 
                                                                            msg_spectra_config->halfFrameSize, 
                                                                            mod_sss_config->sep_gss_mu, 
                                                                            mod_sss_config->sep_gss_lambda,
                                                                            mod_sss_config->epsilon);
                obj->steer2demixing_mvdr = (steer2demixing_mvdr_obj *) NULL;

                obj->demixingsPrev = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                              msg_tracks_config->nTracks, 
                                                              msg_spectra_config->nChannels);

                obj->demixingsNow = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                             msg_tracks_config->nTracks, 
                                                             msg_spectra_config->nChannels);

                obj->demixing2freq = demixing2freq_construct_zero(msg_tracks_config->nTracks,
                                                                  msg_spectra_config->nChannels,
                                                                  msg_spectra_config->halfFrameSize);                

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

                obj->freq2env = freq2env_construct_zero(msg_spectra_config->halfFrameSize);

                obj->noisys = envs_construct_zero(msg_spectra_config->nChannels,
                                                  msg_spectra_config->halfFrameSize);

                obj->demixing2env = demixing2env_construct_zero(msg_tracks_config->nTracks, 
                                                                msg_spectra_config->nChannels, 
                                                                msg_spectra_config->halfFrameSize);

                obj->noisesEst = envs_construct_zero(msg_tracks_config->nTracks, 
                                                     msg_spectra_config->halfFrameSize);

                obj->env2env_mcra = env2env_mcra_construct_zero(msg_tracks_config->nTracks, 
                                                                msg_spectra_config->halfFrameSize,
                                                                mod_sss_config->pf_multi_bSize, 
                                                                mod_sss_config->pf_multi_alphaS, 
                                                                mod_sss_config->pf_multi_L, 
                                                                mod_sss_config->pf_multi_delta, 
                                                                mod_sss_config->pf_multi_alphaD);

                obj->noisesSep = envs_construct_zero(msg_tracks_config->nTracks, 
                                                     msg_spectra_config->halfFrameSize);

                obj->env2env_interf = env2env_interf_construct_zero(msg_tracks_config->nTracks, 
                                                                    msg_spectra_config->halfFrameSize, 
                                                                    mod_sss_config->pf_multi_eta,
                                                                    mod_sss_config->pf_multi_alphaZ);

                obj->interfs = envs_construct_zero(msg_tracks_config->nTracks,
                                                   msg_spectra_config->halfFrameSize);

                obj->env2env_gainspeech = env2env_gainspeech_construct_zero(msg_tracks_config->nTracks,
                                                                            msg_spectra_config->halfFrameSize,
                                                                            mod_sss_config->pf_multi_alphaPmin,
                                                                            mod_sss_config->epsilon);

                obj->gainspeeches = envs_construct_zero(msg_tracks_config->nTracks,
                                                        msg_spectra_config->halfFrameSize);

                obj->snrs = envs_construct_zero(msg_tracks_config->nTracks,
                                                msg_spectra_config->halfFrameSize);

                obj->vs = envs_construct_zero(msg_tracks_config->nTracks,
                                              msg_spectra_config->halfFrameSize);

                obj->env2env_probspeech = env2env_probspeech_construct_zero(msg_tracks_config->nTracks,
                                                                            msg_spectra_config->halfFrameSize, 
                                                                            mod_sss_config->pf_multi_thetaWin, 
                                                                            mod_sss_config->pf_multi_alphaWin,
                                                                            mod_sss_config->pf_multi_maxAbsenceProb, 
                                                                            mod_sss_config->pf_multi_Gmin, 
                                                                            mod_sss_config->pf_multi_winSizeLocal, 
                                                                            mod_sss_config->pf_multi_winSizeGlobal, 
                                                                            mod_sss_config->pf_multi_winSizeFrame);

                obj->probspeeches = envs_construct_zero(msg_tracks_config->nTracks,
                                                        msg_spectra_config->halfFrameSize);

                obj->env2env_gainall = env2env_gainall_construct_zero(msg_tracks_config->nTracks,
                                                                      msg_spectra_config->halfFrameSize,
                                                                      mod_sss_config->pf_multi_Gmin);

                obj->gainalls = envs_construct_zero(msg_tracks_config->nTracks,
                                                    msg_spectra_config->halfFrameSize);

                obj->freq2freq_gain = freq2freq_gain_construct_zero(msg_spectra_config->halfFrameSize);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_powers_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out1 = (msg_spectra_obj *) NULL;
        obj->out2 = (msg_spectra_obj *) NULL;

        return obj;

    }

    void mod_sss_destroy(mod_sss_obj * obj) {

        switch(obj->mode_sep) {

            case 'd':

                beampatterns_destroy(obj->beampatterns_mics);
                beampatterns_destroy(obj->beampatterns_spatialfilter);
                steers_destroy(obj->steers);
                gains_destroy(obj->gains);
                masks_destroy(obj->masks);
                tracks_destroy(obj->tracksPrev);
                tracks_destroy(obj->tracksNow);
                track2gain_destroy(obj->track2gain);
                gain2mask_destroy(obj->gain2mask);
                track2steer_destroy(obj->track2steer);
                steer2demixing_ds_destroy(obj->steer2demixing_ds);
                demixings_destroy(obj->demixingsPrev);
                demixings_destroy(obj->demixingsNow);
                demixing2freq_destroy(obj->demixing2freq);

            break;

            case 'g':

                beampatterns_destroy(obj->beampatterns_mics);
                beampatterns_destroy(obj->beampatterns_spatialfilter);
                steers_destroy(obj->steers);
                gains_destroy(obj->gains);
                masks_destroy(obj->masks);
                tracks_destroy(obj->tracksPrev);
                tracks_destroy(obj->tracksNow);
                track2gain_destroy(obj->track2gain);
                gain2mask_destroy(obj->gain2mask);
                track2steer_destroy(obj->track2steer);
                steer2demixing_gss_destroy(obj->steer2demixing_gss);
                demixings_destroy(obj->demixingsPrev);
                demixings_destroy(obj->demixingsNow);
                demixing2freq_destroy(obj->demixing2freq);

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

                freq2env_destroy(obj->freq2env);
                envs_destroy(obj->noisys);
                demixing2env_destroy(obj->demixing2env);
                envs_destroy(obj->noisesEst);
                env2env_mcra_destroy(obj->env2env_mcra);
                envs_destroy(obj->noisesSep);
                env2env_interf_destroy(obj->env2env_interf);
                envs_destroy(obj->interfs);
                env2env_gainspeech_destroy(obj->env2env_gainspeech);
                envs_destroy(obj->gainspeeches);
                envs_destroy(obj->snrs);
                envs_destroy(obj->vs);
                env2env_probspeech_destroy(obj->env2env_probspeech);
                envs_destroy(obj->probspeeches);
                env2env_gainall_destroy(obj->env2env_gainall);
                envs_destroy(obj->gainalls);
                freq2freq_gain_destroy(obj->freq2freq_gain);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }

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

        if ((msg_spectra_isZero(obj->in1) != msg_powers_isZero(obj->in2)) ||
            (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in3))) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            tracks_copy(obj->tracksPrev,
                        obj->tracksNow);

            tracks_copy(obj->tracksNow,
                        obj->in3->tracks);

            track2gain_process(obj->track2gain, 
                               obj->beampatterns_mics, 
                               obj->beampatterns_spatialfilter, 
                               obj->tracksNow,
                               obj->gains);

            gain2mask_process(obj->gain2mask, 
                              obj->gains, 
                              obj->masks);

            track2steer_process(obj->track2steer, 
                                obj->tracksNow,
                                obj->gains,
                                obj->masks,
                                obj->steers);

            demixings_copy(obj->demixingsPrev, 
                           obj->demixingsNow);

            steer2demixing_ds_process(obj->steer2demixing_ds, 
                                      obj->tracksNow,
                                      obj->steers, 
                                      obj->masks, 
                                      obj->demixingsNow);

            demixing2freq_process(obj->demixing2freq, 
                                  obj->tracksNow,
                                  obj->demixingsNow, 
                                  obj->masks, 
                                  obj->in1->freqs, 
                                  obj->out1->freqs);

            obj->out1->timeStamp = obj->in1->timeStamp;
            
            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);

            rtnValue = -1;

        }

        return rtnValue;        

    }

    int mod_sss_process_dgss(mod_sss_obj * obj) {

        int rtnValue;

        if ((msg_spectra_isZero(obj->in1) != msg_powers_isZero(obj->in2)) ||
            (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in3))) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            tracks_copy(obj->tracksPrev,
                        obj->tracksNow);

            tracks_copy(obj->tracksNow,
                        obj->in3->tracks);

            track2gain_process(obj->track2gain, 
                               obj->beampatterns_mics, 
                               obj->beampatterns_spatialfilter, 
                               obj->tracksNow,
                               obj->gains);

            gain2mask_process(obj->gain2mask, 
                              obj->gains, 
                              obj->masks);

            track2steer_process(obj->track2steer, 
                                obj->tracksNow,
                                obj->gains,
                                obj->masks,
                                obj->steers);

            demixings_copy(obj->demixingsPrev,
                           obj->demixingsNow);

            steer2demixing_gss_process(obj->steer2demixing_gss, 
                                       obj->tracksPrev, 
                                       obj->tracksNow, 
                                       obj->steers, 
                                       obj->masks, 
                                       obj->in1->freqs,
                                       obj->demixingsPrev,
                                       obj->demixingsNow);

            demixing2freq_process(obj->demixing2freq, 
                                  obj->tracksNow,
                                  obj->demixingsNow, 
                                  obj->masks, 
                                  obj->in1->freqs, 
                                  obj->out1->freqs);        

            obj->out1->timeStamp = obj->in1->timeStamp;
            
            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);

            rtnValue = -1;

        }

        return rtnValue;       

    }

    int mod_sss_process_dmvdr(mod_sss_obj * obj) {

        int rtnValue;

        if ((msg_spectra_isZero(obj->in1) != msg_powers_isZero(obj->in2)) ||
            (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in3))) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            freqs_zero(obj->out1->freqs);

            obj->out1->timeStamp = obj->in1->timeStamp;
            
            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);

            rtnValue = -1;

        }

        return rtnValue;    

    }

    int mod_sss_process_mspf(mod_sss_obj * obj) {

        int rtnValue;

        if ((msg_spectra_isZero(obj->in1) != msg_powers_isZero(obj->in2)) ||
            (msg_spectra_isZero(obj->in1) != msg_tracks_isZero(obj->in3))) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            freq2env_process(obj->freq2env,
                             obj->out1->freqs,
                             obj->noisys);

            demixing2env_process(obj->demixing2env,
                                 obj->in3->tracks, 
                                 obj->demixingsNow, 
                                 obj->masks, 
                                 obj->in2->envs,
                                 obj->noisesEst);

            env2env_mcra_process(obj->env2env_mcra, 
                                 obj->in3->tracks, 
                                 obj->noisys, 
                                 obj->noisesEst,
                                 obj->noisesSep);

            env2env_interf_process(obj->env2env_interf, 
                                   obj->in3->tracks, 
                                   obj->noisys, 
                                   obj->noisesSep, 
                                   obj->interfs);           

            env2env_gainspeech_process(obj->env2env_gainspeech, 
                                       obj->in3->tracks, 
                                       obj->noisys, 
                                       obj->interfs, 
                                       obj->gainspeeches, 
                                       obj->snrs, 
                                       obj->vs);

            env2env_probspeech_process(obj->env2env_probspeech, 
                                       obj->in3->tracks,
                                       obj->snrs, 
                                       obj->vs, 
                                       obj->probspeeches);

            env2env_gainall_process(obj->env2env_gainall, 
                                    obj->in3->tracks, 
                                    obj->gainspeeches, 
                                    obj->probspeeches, 
                                    obj->gainalls);

            freq2freq_gain_process(obj->freq2freq_gain, 
                                   obj->out1->freqs, 
                                   obj->gainalls,
                                   obj->out2->freqs);

            obj->out2->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;  

    }

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_powers_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out1, msg_spectra_obj * out2) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->in3 = in3;
        obj->out1 = out1;
        obj->out2 = out2;

    }

    void mod_sss_disconnect(mod_sss_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_powers_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
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