#ifndef __ODAS_ACONNECTOR_POTS
#define __ODAS_ACONNECTOR_POTS

    #include "../connector/con_pots.h"
    #include "../amessage/amsg_pots.h"
    #include "../message/msg_pots.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_pots_obj {

        amsg_pots_obj * in;
        amsg_pots_obj ** outs;
        con_pots_obj * con_pots;
        thread_obj * thread;

    } acon_pots_obj;

    acon_pots_obj * acon_pots_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_pots_cfg * msg_pots_config);

    void acon_pots_destroy(acon_pots_obj * obj);

    void * acon_pots_thread(void * ptr);

#endif