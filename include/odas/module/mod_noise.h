#ifndef __ODAS_MODULE_NOISE
#define __ODAS_MODULE_NOISE

   /**
    * \file     mod_noise.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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