#ifndef __ODAS_AMODULE_MAPPING
#define __ODAS_AMODULE_MAPPING

    #include "../module/mod_mapping.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_mapping_obj {

        mod_mapping_obj * mod_mapping;
        amsg_hops_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;        

    } amod_mapping_obj;

    amod_mapping_obj * amod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config);

    void amod_mapping_destroy(amod_mapping_obj * obj);

    void amod_mapping_connect(amod_mapping_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out);

    void amod_mapping_disconnect(amod_mapping_obj * obj);

    void * amod_mapping_thread(void * ptr);    

#endif