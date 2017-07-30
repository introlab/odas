    
    #include "mod_sspf.h"

    mod_sspf_obj * mod_sspf_construct(const mod_sspf_cfg * mod_sspf_config, const msg_spectra_cfg * msg_spectra_config, const msg_tracks_cfg * msg_tracks_config) {

        mod_sspf_obj * obj;

        obj = (mod_sspf_obj *) malloc(sizeof(mod_sspf_obj));

        obj->nChannels = mod_sspf_config->mics->nChannels;
        obj->nSeps = msg_tracks_config->nTracks;

        obj->beampatterns_mics = directivity_beampattern_mics(mod_sspf_config->mics, mod_sspf_config->nThetas);
        obj->beampatterns_spatialfilter = directivity_beampattern_spatialfilter(mod_sspf_config->spatialfilter, mod_sspf_config->nThetas);

        obj->track2gain = track2gain_construct_zero(obj->nSeps,
                                                    obj->nChannels,
                                                    mod_sspf_config->mics->direction,
                                                    mod_sspf_config->spatialfilter->direction);

        obj->gains = gains_construct_zero(obj->nSeps,
                                          obj->nChannels);

        obj->gain2mask = gain2mask_construct_zero(obj->nSeps,
                                                  obj->nChannels,
                                                  mod_sspf_config->gainMin);

        obj->masks = masks_construct_zero(obj->nSeps,
                                          obj->nChannels);

        obj->freq2freq = freq2freq_construct_zero(msg_spectra_config->halfFrameSize,
                                                  0,
                                                  mod_sspf_config->epsilon);

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_spectra_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;        

        return obj;

    }

    void mod_sspf_destroy(mod_sspf_obj * obj) {

        beampatterns_destroy(obj->beampatterns_mics);
        beampatterns_destroy(obj->beampatterns_spatialfilter);

        track2gain_destroy(obj->track2gain);
        gains_destroy(obj->gains);
        gain2mask_destroy(obj->gain2mask);
        masks_destroy(obj->masks);
        freq2freq_destroy(obj->freq2freq);

        free((void *) obj);

    }

    int mod_sspf_process(mod_sspf_obj * obj) {

        int rtnValue;

        if ((msg_spectra_isZero(obj->in1) == 0) && (msg_spectra_isZero(obj->in2) == 0) && (msg_tracks_isZero(obj->in3) == 0)) {

            if ((obj->in1->timeStamp != obj->in2->timeStamp) || (obj->in1->timeStamp != obj->in3->timeStamp)) {
                printf("Time stamp mismatch.\n");
                exit(EXIT_FAILURE);
            }

            track2gain_process(obj->track2gain,
                               obj->beampatterns_mics,
                               obj->beampatterns_spatialfilter,
                               obj->in3->tracks,
                               obj->gains);

            gain2mask_process(obj->gain2mask,
                              obj->gains,
                              obj->masks);

            freq2freq_process_postfilter(obj->freq2freq, 
                                         obj->in1->freqs,
                                         obj->in2->freqs, 
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

    void mod_sspf_connect(mod_sspf_obj * obj, msg_spectra_obj * in1, msg_spectra_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->in3 = in3;
        obj->out = out;

    }

    void mod_sspf_disconnect(mod_sspf_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_spectra_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;  

    }

    mod_sspf_cfg * mod_sspf_cfg_construct(void) {

        mod_sspf_cfg * cfg;

        cfg = (mod_sspf_cfg *) malloc(sizeof(mod_sspf_cfg));

        cfg->mics = (mics_obj *) NULL;
        cfg->spatialfilter = (spatialfilter_obj *) NULL;

        cfg->epsilon = 0.0f;

        cfg->nThetas = 0;
        cfg->gainMin = 0.0f;

        return cfg;

    }

    void mod_sspf_cfg_destroy(mod_sspf_cfg * cfg) {

        if (cfg->mics != NULL) {
            mics_destroy(cfg->mics);
        }

        if (cfg->spatialfilter != NULL) {
            spatialfilter_destroy(cfg->spatialfilter);
        }

        free((void *) cfg);

    }

    void mod_sspf_cfg_printf(const mod_sspf_cfg * cfg) {

    }
