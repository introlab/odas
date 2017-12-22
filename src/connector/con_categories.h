#ifndef __ODAS_CONNECTOR_CATEGORIES
#define __ODAS_CONNECTOR_CATEGORIES

    #include "../message/msg_categories.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_categories_obj {

        msg_categories_obj * in;
        msg_categories_obj ** outs;

        unsigned int nOuts;

    } con_categories_obj;

    con_categories_obj * con_categories_construct(const unsigned int nOuts, const msg_categories_cfg * msg_categories_config);

    void con_categories_destroy(con_categories_obj * obj);

    int con_categories_process(con_categories_obj * obj);

#endif