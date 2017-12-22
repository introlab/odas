#ifndef __ODAS_AMODULE_RESAMPLE
#define __ODAS_AMODULE_RESAMPLE

    #include "../module/mod_resample.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_resample_obj {

        mod_resample_obj * mod_resample;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;    

    } amod_resample_obj;

    amod_resample_obj * amod_resample_construct(const mod_resample_cfg * mod_resample_config, const msg_hops_cfg * msg_hops_in_config, const msg_hops_cfg * msg_hops_out_config);

    void amod_resample_destroy(amod_resample_obj * obj);

    void amod_resample_connect(amod_resample_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_resample_disconnect(amod_resample_obj * obj);

    void * amod_resample_thread(void * ptr);    

#endif