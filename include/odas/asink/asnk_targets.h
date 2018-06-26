#ifndef __ODAS_ASINK_TARGETS
#define __ODAS_ASINK_TARGETS


    #include "../amessage/amsg_targets.h"
    #include "../sink/snk_targets.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_targets_obj {

        snk_targets_obj * snk_targets;
        amsg_targets_obj * in;
        thread_obj * thread;

    } asnk_targets_obj;

    asnk_targets_obj * asnk_targets_construct(const snk_targets_cfg * snk_targets_config, const msg_targets_cfg * msg_targets_config);

    void asnk_targets_destroy(asnk_targets_obj * obj);

    void asnk_targets_connect(asnk_targets_obj * obj, amsg_targets_obj * in);

    void asnk_targets_disconnect(asnk_targets_obj * obj);

    void * asnk_targets_thread(void * ptr);

#endif