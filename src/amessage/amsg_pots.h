#ifndef __ODAS_AMESSAGE_POTS
#define __ODAS_AMESSAGE_POTS

    #include <stdlib.h>

    #include "../message/msg_pots.h"
    #include "../utils/fifo.h"

    typedef struct amsg_pots_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_pots_obj;

    amsg_pots_obj * amsg_pots_construct(const unsigned int nMessages, const msg_pots_cfg * msg_pots_config);

    void amsg_pots_destroy(amsg_pots_obj * obj);

    msg_pots_obj * amsg_pots_filled_pop(amsg_pots_obj * obj);

    void amsg_pots_filled_push(amsg_pots_obj * obj, msg_pots_obj * msg_pots);

    msg_pots_obj * amsg_pots_empty_pop(amsg_pots_obj * obj);

    void amsg_pots_empty_push(amsg_pots_obj * obj, msg_pots_obj * msg_pots);

#endif