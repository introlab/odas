#ifndef __ODAS_ACONNECTOR_HOPS
#define __ODAS_ACONNECTOR_HOPS

    #include "../connector/con_hops.h"
    #include "../amessage/amsg_hops.h"
    #include "../message/msg_hops.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_hops_obj {

        amsg_hops_obj * in;
        amsg_hops_obj ** outs;
        con_hops_obj * con_hops;
        thread_obj * thread;

    } acon_hops_obj;

    acon_hops_obj * acon_hops_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_hops_cfg * msg_hops_config);

    void acon_hops_destroy(acon_hops_obj * obj);

    void * acon_hops_thread(void * ptr);

#endif