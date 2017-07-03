#ifndef __ODAS_ASINK_POTS
#define __ODAS_ASINK_POTS

    #include "../amessage/amsg_pots.h"
    #include "../sink/snk_pots.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_pots_obj {

        snk_pots_obj * snk_pots;
        amsg_pots_obj * in;
        thread_obj * thread;

    } asnk_pots_obj;

    asnk_pots_obj * asnk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config);

    void asnk_pots_destroy(asnk_pots_obj * obj);

    void asnk_pots_connect(asnk_pots_obj * obj, amsg_pots_obj * in);

    void asnk_pots_disconnect(asnk_pots_obj * obj);

    void * asnk_pots_thread(void * ptr);

#endif