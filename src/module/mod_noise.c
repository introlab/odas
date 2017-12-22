    
    #include "mod_noise.h"

    mod_noise_obj * mod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config) {

        mod_noise_obj * obj;

        obj = (mod_noise_obj *) malloc(sizeof(mod_noise_obj));

        obj->freq2env = freq2env_construct_zero(msg_spectra_config->halfFrameSize);

        obj->envs = envs_construct_zero(msg_powers_config->nChannels,
                                        msg_powers_config->halfFrameSize);

        obj->env2env_mcra = env2env_mcra_construct_zero(msg_powers_config->nChannels, 
                                                        msg_powers_config->halfFrameSize, 
                                                        mod_noise_config->bSize, 
                                                        mod_noise_config->alphaS, 
                                                        mod_noise_config->L, 
                                                        mod_noise_config->delta, 
                                                        mod_noise_config->alphaD);

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_powers_obj *) NULL;

        return obj;

    }

    void mod_noise_destroy(mod_noise_obj * obj) {

        freq2env_destroy(obj->freq2env);
        envs_destroy(obj->envs);
        env2env_mcra_destroy(obj->env2env_mcra);

        free((void *) obj);

    }

    int mod_noise_process(mod_noise_obj * obj) {

        int rtnValue;

        if (msg_spectra_isZero(obj->in) == 0) {

            freq2env_process(obj->freq2env,
                             obj->in->freqs,
                             obj->envs);

            env2env_mcra_process(obj->env2env_mcra,
                                 NULL,
                                 obj->envs,
                                 NULL,
                                 obj->out->envs);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_powers_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_noise_connect(mod_noise_obj * obj, msg_spectra_obj * in, msg_powers_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_noise_disconnect(mod_noise_obj * obj) {

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_powers_obj *) NULL;

    }

    mod_noise_cfg * mod_noise_cfg_construct(void) {

        mod_noise_cfg * cfg;

        cfg = (mod_noise_cfg *) malloc(sizeof(mod_noise_cfg));

        return cfg;

    }

    void mod_noise_cfg_destroy(mod_noise_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_noise_cfg_printf(const mod_noise_cfg * cfg) {



    }