#ifndef __ODAS_AMODULE_ISTFT
#define __ODAS_AMODULE_ISTFT

    #include "../module/mod_istft.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_istft_obj {

        mod_istft_obj * mod_istft;
        amsg_spectra_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;    

    } amod_istft_obj;

    amod_istft_obj * amod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config);

    void amod_istft_destroy(amod_istft_obj * obj);

    void amod_istft_connect(amod_istft_obj * obj, amsg_spectra_obj * in, amsg_hops_obj * out);

    void amod_istft_disconnect(amod_istft_obj * obj);

    void * amod_istft_thread(void * ptr);    

#endif