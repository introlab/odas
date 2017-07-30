    
    #include "mod_sss.h"

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_spectra_cfg * msg_spectra_config, const msg_tracks_cfg * msg_tracks_config) {

        mod_sss_obj * obj;

        obj = (mod_sss_obj *) malloc(sizeof(mod_sss_obj));

        obj->nChannels = mod_sss_config->mics->nChannels;
        obj->nSeps = msg_tracks_config->nTracks;

        obj->beampatterns_mics = directivity_beampattern_mics(mod_sss_config->mics, mod_sss_config->nThetas);
        obj->beampatterns_spatialfilter = directivity_beampattern_spatialfilter(mod_sss_config->spatialfilter, mod_sss_config->nThetas);

        obj->track2shift = track2shift_construct_zero(obj->nSeps,
                                                      obj->nChannels,
                                                      mod_sss_config->samplerate->mu,
                                                      mod_sss_config->soundspeed->mu,
                                                      mod_sss_config->mics->mu);

        obj->shifts = shifts_construct_zero(obj->nSeps,
                                            obj->nChannels);

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

        obj->freq2freq = freq2freq_construct_zero(msg_spectra_config->halfFrameSize,
                                                  0,
                                                  0.0f);

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;        

        return obj;

    }

    void mod_sss_destroy(mod_sss_obj * obj) {

        beampatterns_destroy(obj->beampatterns_mics);
        beampatterns_destroy(obj->beampatterns_spatialfilter);

        track2shift_destroy(obj->track2shift);
        shifts_destroy(obj->shifts);
        track2gain_destroy(obj->track2gain);
        gains_destroy(obj->gains);
        gain2mask_destroy(obj->gain2mask);
        masks_destroy(obj->masks);
        freq2freq_destroy(obj->freq2freq);

        free((void *) obj);

    }

    int mod_sss_process(mod_sss_obj * obj) {

        int rtnValue;

        if ((msg_spectra_isZero(obj->in1) == 0) && (msg_tracks_isZero(obj->in2) == 0)) {

            if (obj->in1->timeStamp != obj->in2->timeStamp) {
                printf("Time stamp mismatch.\n");
                exit(EXIT_FAILURE);
            }

            track2shift_process(obj->track2shift,
                                obj->in2->tracks,
                                obj->shifts);

            track2gain_process(obj->track2gain,
                               obj->beampatterns_mics,
                               obj->beampatterns_spatialfilter,
                               obj->in2->tracks,
                               obj->gains);

            gain2mask_process(obj->gain2mask,
                              obj->gains,
                              obj->masks);

            freq2freq_process_delaysum(obj->freq2freq,
                                       obj->in1->freqs,
                                       obj->shifts,
                                       obj->gains,
                                       obj->masks,
                                       obj->out->freqs);

            obj->out->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;

    }

    void mod_sss_disconnect(mod_sss_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

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