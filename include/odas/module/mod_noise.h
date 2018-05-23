#ifndef __ODAS_MODULE_NOISE
#define __ODAS_MODULE_NOISE

   /**
    * \file     mod_noise.h
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

    #include "../system/freq2env.h"
    #include "../system/env2env.h"
    #include "../message/msg_spectra.h"
    #include "../message/msg_powers.h"

    typedef struct mod_noise_obj {

        freq2env_obj * freq2env;
        envs_obj * envs;
        env2env_mcra_obj * env2env_mcra;

        msg_spectra_obj * in;
        msg_powers_obj * out;        

        char enabled;

    } mod_noise_obj;

    typedef struct mod_noise_cfg {
        
        unsigned int bSize;
        float alphaS;
        unsigned int L;
        float delta;
        float alphaD;

    } mod_noise_cfg;

    mod_noise_obj * mod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config);

    void mod_noise_destroy(mod_noise_obj * obj);

    int mod_noise_process(mod_noise_obj * obj);

    void mod_noise_connect(mod_noise_obj * obj, msg_spectra_obj * in, msg_powers_obj * out);

    void mod_noise_disconnect(mod_noise_obj * obj);

    void mod_noise_enable(mod_noise_obj * obj);

    void mod_noise_disable(mod_noise_obj * obj);

    mod_noise_cfg * mod_noise_cfg_construct(void);

    void mod_noise_cfg_destroy(mod_noise_cfg * cfg);

    void mod_noise_cfg_printf(const mod_noise_cfg * cfg);

#endif