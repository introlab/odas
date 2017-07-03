#ifndef __ODAS_AMODULE_STFT
#define __ODAS_AMODULE_STFT

    #include "../module/mod_stft.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_stft_obj {

        mod_stft_obj * mod_stft;
        amsg_hops_obj * in;
        amsg_spectra_obj * out;
        thread_obj * thread;    

    } amod_stft_obj;

    amod_stft_obj * amod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config);

    void amod_stft_destroy(amod_stft_obj * obj);

    void amod_stft_connect(amod_stft_obj * obj, amsg_hops_obj * in, amsg_spectra_obj * out);

    void amod_stft_disconnect(amod_stft_obj * obj);

    void * amod_stft_thread(void * ptr);    

#endif