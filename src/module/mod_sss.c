    
    #include "mod_sss.h"

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config, const msg_envs_cfg * msg_envs_config) {

        mod_sss_obj * obj;

        obj = (mod_sss_obj *) malloc(sizeof(mod_sss_obj));

        obj->nChannels = mod_sss_config->mics->nChannels;
        obj->nSeps = msg_tracks_config->nTracks;

        obj->beampatterns_mics = directivity_beampattern_mics(mod_sss_config->mics, mod_sss_config->nThetas);
        obj->beampatterns_spatialfilter = directivity_beampattern_spatialfilter(mod_sss_config->spatialfilter, mod_sss_config->nThetas);

        obj->track2gain = track2gain_construct_zero(obj->nSeps,
                                                    obj->nChannels,
                                                    mod_sss_config->mics->direction,
                                                    mod_sss_config->spatialfilter->direction);

        obj->gains = gains_construct_zero(obj->nSeps,
                                          obj->nChannels);

        obj->gain2mask = gain2mask_construct_zero(obj->nSeps,
                                                  obj->nChannels,
                                                  mod_sss_config->gainMin);

        obj->masks = masks_construct_zero(obj->nSeps,
                                          obj->nChannels);

        obj->track2steer = track2steer_construct_zero(obj->nSeps, 
                                                      obj->nChannels, 
                                                      msg_spectra_config->halfFrameSize, 
                                                      mod_sss_config->soundspeed->mu, 
                                                      mod_sss_config->samplerate->mu,
                                                      mod_sss_config->mics->mu);

        obj->W = steers_construct_zero(msg_spectra_config->halfFrameSize,
                                       obj->nSeps,
                                       obj->nChannels);

        obj->steer2freq = steer2freq_construct_zero(obj->nSeps, 
                                                    obj->nChannels, 
                                                    msg_spectra_config->halfFrameSize);

        obj->steer2env = steer2env_construct_zero(obj->nSeps,
                                                  obj->nChannels,
                                                  msg_envs_config->halfFrameSize);

        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nSeps);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * obj->nSeps);

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out1 = (msg_spectra_obj *) NULL;
        obj->out2 = (msg_envs_obj *) NULL;

        return obj;

    }

    void mod_sss_destroy(mod_sss_obj * obj) {

        beampatterns_destroy(obj->beampatterns_mics);
        beampatterns_destroy(obj->beampatterns_spatialfilter);

        track2gain_destroy(obj->track2gain);
        gains_destroy(obj->gains);
        gain2mask_destroy(obj->gain2mask);
        masks_destroy(obj->masks);

        track2steer_destroy(obj->track2steer);
        steers_destroy(obj->W);
        steer2freq_destroy(obj->steer2freq);
        steer2env_destroy(obj->steer2env);

        free((void *) obj);

    }

    int mod_sss_process(mod_sss_obj * obj) {

        int rtnValue;
        unsigned int iSep;

        if ((msg_spectra_isZero(obj->in1) == 0) && (msg_tracks_isZero(obj->in2) == 0)) {

            if (obj->in1->timeStamp != obj->in2->timeStamp) {
                printf("Time stamp mismatch.\n");
                exit(EXIT_FAILURE);
            }

            // Generate the gain according to each source direction
            track2gain_process(obj->track2gain,
                               obj->beampatterns_mics,
                               obj->beampatterns_spatialfilter,
                               obj->in2->tracks,
                               obj->gains);

            // Generate masks from gains
            gain2mask_process(obj->gain2mask,
                              obj->gains,
                              obj->masks);
           
            // Generate the demixing matrix W with gains
            track2steer_process_demixing(obj->track2steer,
                                         obj->in2->tracks,
                                         obj->gains,
                                         obj->masks,
                                         obj->W);            

            // Apply W to get separated spectra
            steer2freq_process(obj->steer2freq, 
                               obj->in2->tracks,
                               obj->W,
                               obj->masks,
                               obj->in1->freqs, 
                               obj->out1->freqs);

            // Apply W to get separated envelope
            steer2env_process(obj->steer2env,
                              obj->in2->tracks, 
                              obj->W,
                              obj->masks,
                              obj->in1->freqs,
                              obj->out2->envs);

            obj->out1->timeStamp = obj->in1->timeStamp;
            obj->out2->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);
            msg_envs_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out1, msg_envs_obj * out2) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out1 = out1;
        obj->out2 = out2;

    }

    void mod_sss_disconnect(mod_sss_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out1 = (msg_spectra_obj *) NULL;
        obj->out2 = (msg_envs_obj *) NULL;

    }

    mod_sss_cfg * mod_sss_cfg_construct(void) {

        mod_sss_cfg * cfg;

        cfg = (mod_sss_cfg *) malloc(sizeof(mod_sss_cfg));

        cfg->mics = (mics_obj *) NULL;
        cfg->spatialfilter = (spatialfilter_obj *) NULL;
        cfg->samplerate = (samplerate_obj *) NULL;
        cfg->soundspeed = (soundspeed_obj *) NULL;

        cfg->nThetas = 0;
        cfg->gainMin = 0.0f;

        return cfg;

    }

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg) {

        if (cfg->mics != NULL) {
            mics_destroy(cfg->mics);
        }

        if (cfg->spatialfilter != NULL) {
            spatialfilter_destroy(cfg->spatialfilter);
        }

        if (cfg->samplerate != NULL) {
            samplerate_destroy(cfg->samplerate);
        }

        if (cfg->soundspeed != NULL) {
            soundspeed_destroy(cfg->soundspeed);
        }

        free((void *) cfg);

    }

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg) {
        
    }