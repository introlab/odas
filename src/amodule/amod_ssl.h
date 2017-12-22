#ifndef __ODAS_AMODULE_SSL
#define __ODAS_AMODULE_SSL

    #include "../module/mod_ssl.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_powers.h"
    #include "../amessage/amsg_pots.h"
    #include "../general/thread.h"

    typedef struct amod_ssl_obj {

        mod_ssl_obj * mod_ssl;
        amsg_spectra_obj * in;
        amsg_pots_obj * out;
        thread_obj * thread;    

    } amod_ssl_obj;

    amod_ssl_obj * amod_ssl_construct(const mod_ssl_cfg * mod_ssl_config, const msg_spectra_cfg * msg_spectra_config, const msg_pots_cfg * msg_pots_config);

    void amod_ssl_destroy(amod_ssl_obj * obj);

    void amod_ssl_connect(amod_ssl_obj * obj, amsg_spectra_obj * in, amsg_pots_obj * out);

    void amod_ssl_disconnect(amod_ssl_obj * obj);

    void * amod_ssl_thread(void * ptr);    

#endif