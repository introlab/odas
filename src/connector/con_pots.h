#ifndef __ODAS_CONNECTOR_POTS
#define __ODAS_CONNECTOR_POTS

    #include "../message/msg_pots.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_pots_obj {

        msg_pots_obj * in;
        msg_pots_obj ** outs;

        unsigned int nOuts;

    } con_pots_obj;

    con_pots_obj * con_pots_construct(const unsigned int nOuts, const msg_pots_cfg * msg_pots_config);

    void con_pots_destroy(con_pots_obj * obj);

    int con_pots_process(con_pots_obj * obj);

#endif