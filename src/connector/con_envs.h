#ifndef __ODAS_CONNECTOR_ENVS
#define __ODAS_CONNECTOR_ENVS

    #include "../message/msg_envs.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_envs_obj {

        msg_envs_obj * in;
        msg_envs_obj ** outs;

        unsigned int nOuts;

    } con_envs_obj;

    con_envs_obj * con_envs_construct(const unsigned int nOuts, const msg_envs_cfg * msg_envs_config);

    void con_envs_destroy(con_envs_obj * obj);

    int con_envs_process(con_envs_obj * obj);

#endif