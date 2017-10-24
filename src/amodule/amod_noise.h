#ifndef __ODAS_AMODULE_NOISE
#define __ODAS_AMODULE_NOISE

    #include "../module/mod_noise.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_powers.h"
    #include "../general/thread.h"

    typedef struct amod_noise_obj {

        mod_noise_obj * mod_noise;
        amsg_spectra_obj * in;
        amsg_powers_obj * out;
        thread_obj * thread;    

    } amod_noise_obj;

    amod_noise_obj * amod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config);

    void amod_noise_destroy(amod_noise_obj * obj);

    void amod_noise_connect(amod_noise_obj * obj, amsg_spectra_obj * in, amsg_powers_obj * out);

    void amod_noise_disconnect(amod_noise_obj * obj);

    void * amod_noise_thread(void * ptr);    

#endif