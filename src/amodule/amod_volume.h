#ifndef __ODAS_AMODULE_VOLUME
#define __ODAS_AMODULE_VOLUME

    #include "../module/mod_volume.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_volume_obj {

        mod_volume_obj * mod_volume;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;        

    } amod_volume_obj;

    amod_volume_obj * amod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config);

    void amod_volume_destroy(amod_volume_obj * obj);

    void amod_volume_connect(amod_volume_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_volume_disconnect(amod_volume_obj * obj);

    void * amod_volume_thread(void * ptr);    

#endif