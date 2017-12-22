#ifndef __ODAS_MODULE_NOISE
#define __ODAS_MODULE_NOISE

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

    mod_noise_cfg * mod_noise_cfg_construct(void);

    void mod_noise_cfg_destroy(mod_noise_cfg * cfg);

    void mod_noise_cfg_printf(const mod_noise_cfg * cfg);

#endif