#ifndef __ODAS_AMODULE_GAIN
#define __ODAS_AMODULE_GAIN

    #include "../module/mod_gain.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_gain_obj {

        mod_gain_obj * mod_gain;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;    

    } amod_gain_obj;

    amod_gain_obj * amod_gain_construct(const mod_gain_cfg * mod_gain_config, const msg_hops_cfg * msg_hops_config);

    void amod_gain_destroy(amod_gain_obj * obj);

    void amod_gain_connect(amod_gain_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_gain_disconnect(amod_gain_obj * obj);

    void * amod_gain_thread(void * ptr);    

#endif