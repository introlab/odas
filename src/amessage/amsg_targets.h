#ifndef __ODAS_AMESSAGE_TARGETS
#define __ODAS_AMESSAGE_TARGETS

    #include <stdlib.h>

    #include "../message/msg_targets.h"
    #include "../utils/fifo.h"

    typedef struct amsg_targets_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_targets_obj;

    amsg_targets_obj * amsg_targets_construct(const unsigned int nMessages, const msg_targets_cfg * msg_targets_config);

    void amsg_targets_destroy(amsg_targets_obj * obj);

    msg_targets_obj * amsg_targets_filled_pop(amsg_targets_obj * obj);

    void amsg_targets_filled_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets);

    msg_targets_obj * amsg_targets_empty_pop(amsg_targets_obj * obj);

    void amsg_targets_empty_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets);

#endif