#ifndef __ODAS_ACONNECTOR_POWERS
#define __ODAS_ACONNECTOR_POWERS

    #include "../connector/con_powers.h"
    #include "../amessage/amsg_powers.h"
    #include "../message/msg_powers.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_powers_obj {

        amsg_powers_obj * in;
        amsg_powers_obj ** outs;
        con_powers_obj * con_powers;
        thread_obj * thread;

    } acon_powers_obj;

    acon_powers_obj * acon_powers_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_powers_cfg * msg_powers_config);

    void acon_powers_destroy(acon_powers_obj * obj);

    void * acon_powers_thread(void * ptr);

#endif