#ifndef __ODAS_ASOURCE_HOPS
#define __ODAS_ASOURCE_HOPS

    #include "../amessage/amsg_hops.h"
    #include "../source/src_hops.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asrc_hops_obj {

        src_hops_obj * src_hops;
        amsg_hops_obj * out;
        thread_obj * thread;

    } asrc_hops_obj;

    asrc_hops_obj * asrc_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config);

    void asrc_hops_destroy(asrc_hops_obj * obj);

    void asrc_hops_connect(asrc_hops_obj * obj, amsg_hops_obj * out);

    void asrc_hops_disconnect(asrc_hops_obj * obj);

    void * asrc_hops_thread(void * ptr);

#endif