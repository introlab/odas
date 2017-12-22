#ifndef __ODAS_ACONNECTOR_CATEGORIES
#define __ODAS_ACONNECTOR_CATEGORIES

    #include "../connector/con_categories.h"
    #include "../amessage/amsg_categories.h"
    #include "../message/msg_categories.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_categories_obj {

        amsg_categories_obj * in;
        amsg_categories_obj ** outs;
        con_categories_obj * con_categories;
        thread_obj * thread;

    } acon_categories_obj;

    acon_categories_obj * acon_categories_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_categories_cfg * msg_categories_config);

    void acon_categories_destroy(acon_categories_obj * obj);

    void * acon_categories_thread(void * ptr);

#endif