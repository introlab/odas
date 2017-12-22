#ifndef __ODAS_CONNECTOR_TARGETS
#define __ODAS_CONNECTOR_TARGETS

    #include "../message/msg_targets.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_targets_obj {

        msg_targets_obj * in;
        msg_targets_obj ** outs;

        unsigned int nOuts;

    } con_targets_obj;

    con_targets_obj * con_targets_construct(const unsigned int nOuts, const msg_targets_cfg * msg_targets_config);

    void con_targets_destroy(con_targets_obj * obj);

    int con_targets_process(con_targets_obj * obj);

#endif