#ifndef __ODAS_AMODULE_SST
#define __ODAS_AMODULE_SST

    #include "../module/mod_ssl.h"
    #include "../module/mod_sst.h"
    #include "../amessage/amsg_pots.h"
    #include "../amessage/amsg_tracks.h"
    #include "../general/thread.h"

    typedef struct amod_sst_obj {

        mod_sst_obj * mod_sst;
        amsg_pots_obj * in;
        amsg_tracks_obj * out;
        thread_obj * thread;    

    } amod_sst_obj;

    amod_sst_obj * amod_sst_construct(const mod_sst_cfg * mod_sst_config, const mod_ssl_cfg * mod_ssl_config, const msg_pots_cfg * msg_pots_config, const msg_tracks_cfg * msg_tracks_config);

    void amod_sst_destroy(amod_sst_obj * obj);

    void amod_sst_connect(amod_sst_obj * obj, amsg_pots_obj * in, amsg_tracks_obj * out);

    void amod_sst_disconnect(amod_sst_obj * obj);

    void * amod_sst_thread(void * ptr);    

#endif