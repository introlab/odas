#ifndef __ODAS_ACONNECTOR_TARGETS
#define __ODAS_ACONNECTOR_TARGETS

    #include "../connector/con_targets.h"
    #include "../amessage/amsg_targets.h"
    #include "../message/msg_targets.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_targets_obj {

        amsg_targets_obj * in;
        amsg_targets_obj ** outs;
        con_targets_obj * con_targets;
        thread_obj * thread;

    } acon_targets_obj;

    acon_targets_obj * acon_targets_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_targets_cfg * msg_targets_config);

    void acon_targets_destroy(acon_targets_obj * obj);

    void * acon_targets_thread(void * ptr);

#endif