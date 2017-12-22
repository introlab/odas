#ifndef __ODAS_ASINK_HOPS
#define __ODAS_ASINK_HOPS

    #include "../amessage/amsg_hops.h"
    #include "../sink/snk_hops.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_hops_obj {

        snk_hops_obj * snk_hops;
        amsg_hops_obj * in;
        thread_obj * thread;

    } asnk_hops_obj;

    asnk_hops_obj * asnk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config);

    void asnk_hops_destroy(asnk_hops_obj * obj);

    void asnk_hops_connect(asnk_hops_obj * obj, amsg_hops_obj * in);

    void asnk_hops_disconnect(asnk_hops_obj * obj);

    void * asnk_hops_thread(void * ptr);

#endif