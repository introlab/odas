#ifndef __ODAS_CONNECTOR_HOPS
#define __ODAS_CONNECTOR_HOPS

    #include "../message/msg_hops.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_hops_obj {

        msg_hops_obj * in;
        msg_hops_obj ** outs;

        unsigned int nOuts;

    } con_hops_obj;

    con_hops_obj * con_hops_construct(const unsigned int nOuts, const msg_hops_cfg * msg_hops_config);

    void con_hops_destroy(con_hops_obj * obj);

    int con_hops_process(con_hops_obj * obj);

#endif