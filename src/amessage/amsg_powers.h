#ifndef __ODAS_AMESSAGE_POWERS
#define __ODAS_AMESSAGE_POWERS

    #include <stdlib.h>

    #include "../message/msg_powers.h"
    #include "../utils/fifo.h"

    typedef struct amsg_powers_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_powers_obj;

    amsg_powers_obj * amsg_powers_construct(const unsigned int nMessages, const msg_powers_cfg * msg_powers_config);

    void amsg_powers_destroy(amsg_powers_obj * obj);

    msg_powers_obj * amsg_powers_filled_pop(amsg_powers_obj * obj);

    void amsg_powers_filled_push(amsg_powers_obj * obj, msg_powers_obj * msg_powers);

    msg_powers_obj * amsg_powers_empty_pop(amsg_powers_obj * obj);

    void amsg_powers_empty_push(amsg_powers_obj * obj, msg_powers_obj * msg_powers);

#endif