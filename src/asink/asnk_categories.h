#ifndef __ODAS_ASINK_CATEGORIES
#define __ODAS_ASINK_CATEGORIES

    #include "../amessage/amsg_categories.h"
    #include "../sink/snk_categories.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_categories_obj {

        snk_categories_obj * snk_categories;
        amsg_categories_obj * in;
        thread_obj * thread;

    } asnk_categories_obj;

    asnk_categories_obj * asnk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config);

    void asnk_categories_destroy(asnk_categories_obj * obj);

    void asnk_categories_connect(asnk_categories_obj * obj, amsg_categories_obj * in);

    void asnk_categories_disconnect(asnk_categories_obj * obj);

    void * asnk_categories_thread(void * ptr);

#endif