    
    #include "mod_sspf.h"

    mod_sspf_obj * mod_sspf_construct(const mod_sspf_cfg * mod_sspf_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config, const msg_envs_cfg * msg_envs_config) {

        mod_sspf_obj * obj;

        obj = (mod_sspf_obj *) malloc(sizeof(mod_sspf_obj));

        obj->nSeps = msg_spectra_config->nChannels;
        obj->halfFrameSize = msg_spectra_config->halfFrameSize;

        obj->alpha = mod_sspf_config->alpha;
        obj->beta = mod_sspf_config->beta;
        obj->Ginterf = mod_sspf_config->Ginterf;
        obj->epsilon = mod_sspf_config->epsilon;

        obj->freq2env = freq2env_construct_zero(obj->halfFrameSize, obj->nSeps);
        obj->envs = envs_construct_zero(obj->nSeps, obj->halfFrameSize);
        obj->freq2freq = freq2freq_construct_zero(obj->halfFrameSize, 0, 0, obj->epsilon, obj->alpha, obj->beta, obj->Ginterf);

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_envs_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

        return obj;

    }

    void mod_sspf_destroy(mod_sspf_obj * obj) {

        freq2env_destroy(obj->freq2env);
        envs_destroy(obj->envs);
        freq2freq_destroy(obj->freq2freq);

        free((void *) obj);

    }

    int mod_sspf_process(mod_sspf_obj * obj) {

        int rtnValue;

        if ((msg_spectra_isZero(obj->in1) == 0) && (msg_envs_isZero(obj->in2) == 0) && (msg_tracks_isZero(obj->in3) == 0)) {

            if ((obj->in1->timeStamp != obj->in2->timeStamp) || (obj->in1->timeStamp != obj->in3->timeStamp)) {
                printf("Time stamp mismatch.\n");
                exit(EXIT_FAILURE);
            }

            freq2env_process(obj->freq2env, obj->in1->freqs, obj->envs);
            freq2freq_process_postfilter(obj->freq2freq, obj->in3->tracks, obj->in1->freqs, obj->envs, obj->in2->envs, obj->out->freqs);

            obj->out->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out);

            rtnValue = -1;            

        }

        return rtnValue;

    }

    void mod_sspf_connect(mod_sspf_obj * obj, msg_spectra_obj * in1, msg_envs_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->in3 = in3;
        obj->out = out;

    }

    void mod_sspf_disconnect(mod_sspf_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_envs_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

    }

    mod_sspf_cfg * mod_sspf_cfg_construct(void) {

        mod_sspf_cfg * cfg;

        cfg = (mod_sspf_cfg *) malloc(sizeof(mod_sspf_cfg));

        cfg->alpha = 0.0f;
        cfg->beta = 0.0f;
        cfg->Ginterf = 0.0f;
        cfg->epsilon = 0.0f;

        return cfg;

    }

    void mod_sspf_cfg_destroy(mod_sspf_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_sspf_cfg_printf(const mod_sspf_cfg * cfg) {

    }