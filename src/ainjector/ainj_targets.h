#ifndef __ODAS_AINJECTOR_TARGETS
#define __ODAS_AINJECTOR_TARGETS

    #include "../injector/inj_targets.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_targets.h"
    #include "../general/thread.h"

    typedef struct ainj_targets_obj {

        inj_targets_obj * inj_targets;
        amsg_hops_obj * in;
        amsg_targets_obj * out;
        thread_obj * thread;    

    } ainj_targets_obj;

    ainj_targets_obj * ainj_targets_construct(const inj_targets_cfg * inj_targets_config, const msg_hops_cfg * msg_hops_config, const msg_targets_cfg * msg_targets_config);

    void ainj_targets_destroy(ainj_targets_obj * obj);

    void ainj_targets_connect(ainj_targets_obj * obj, amsg_hops_obj * in, amsg_targets_obj * out);

    void ainj_targets_disconnect(ainj_targets_obj * obj);

    void * ainj_targets_thread(void * ptr); 

#endif