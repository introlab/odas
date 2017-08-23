#ifndef __ODAS_ACONNECTOR_ENVS
#define __ODAS_ACONNECTOR_ENVS

    #include "../connector/con_envs.h"
    #include "../amessage/amsg_envs.h"
    #include "../message/msg_envs.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_envs_obj {

        amsg_envs_obj * in;
        amsg_envs_obj ** outs;
        con_envs_obj * con_envs;
        thread_obj * thread;

    } acon_envs_obj;

    acon_envs_obj * acon_envs_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_envs_cfg * msg_envs_config);

    void acon_envs_destroy(acon_envs_obj * obj);

    void * acon_envs_thread(void * ptr);

#endif