
   /**
    * \file     mod_noise.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <module/mod_noise.h>

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
