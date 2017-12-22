#ifndef __ODAS_AMESSAGE_HOPS
#define __ODAS_AMESSAGE_HOPS

    #include <stdlib.h>

    #include "../message/msg_hops.h"
    #include "../utils/fifo.h"

    typedef struct amsg_hops_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_hops_obj;

    amsg_hops_obj * amsg_hops_construct(const unsigned int nMessages, const msg_hops_cfg * msg_hops_config);

    void amsg_hops_destroy(amsg_hops_obj * obj);

    msg_hops_obj * amsg_hops_filled_pop(amsg_hops_obj * obj);

    void amsg_hops_filled_push(amsg_hops_obj * obj, msg_hops_obj * msg_hops);

    msg_hops_obj * amsg_hops_empty_pop(amsg_hops_obj * obj);

    void amsg_hops_empty_push(amsg_hops_obj * obj, msg_hops_obj * msg_hops);

#endif