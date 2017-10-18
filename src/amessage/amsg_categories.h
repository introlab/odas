#ifndef __ODAS_AMESSAGE_CATEGORIES
#define __ODAS_AMESSAGE_CATEGORIES

    #include <stdlib.h>

    #include "../message/msg_categories.h"
    #include "../utils/fifo.h"

    typedef struct amsg_categories_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_categories_obj;

    amsg_categories_obj * amsg_categories_construct(const unsigned int nMessages, const msg_categories_cfg * msg_categories_config);

    void amsg_categories_destroy(amsg_categories_obj * obj);

    msg_categories_obj * amsg_categories_filled_pop(amsg_categories_obj * obj);

    void amsg_categories_filled_push(amsg_categories_obj * obj, msg_categories_obj * msg_categories);

    msg_categories_obj * amsg_categories_empty_pop(amsg_categories_obj * obj);

    void amsg_categories_empty_push(amsg_categories_obj * obj, msg_categories_obj * msg_categories);

#endif