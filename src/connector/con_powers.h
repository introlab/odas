#ifndef __ODAS_CONNECTOR_POWERS
#define __ODAS_CONNECTOR_POWERS

    #include "../message/msg_powers.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_powers_obj {

        msg_powers_obj * in;
        msg_powers_obj ** outs;

        unsigned int nOuts;

    } con_powers_obj;

    con_powers_obj * con_powers_construct(const unsigned int nOuts, const msg_powers_cfg * msg_powers_config);

    void con_powers_destroy(con_powers_obj * obj);

    int con_powers_process(con_powers_obj * obj);

#endif