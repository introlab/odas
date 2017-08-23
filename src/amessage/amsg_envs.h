#ifndef __ODAS_AMESSAGE_ENVS
#define __ODAS_AMESSAGE_ENVS

    #include <stdlib.h>

    #include "../message/msg_envs.h"
    #include "../utils/fifo.h"

    typedef struct amsg_envs_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_envs_obj;

    amsg_envs_obj * amsg_envs_construct(const unsigned int nMessages, const msg_envs_cfg * msg_envs_config);

    void amsg_envs_destroy(amsg_envs_obj * obj);

    msg_envs_obj * amsg_envs_filled_pop(amsg_envs_obj * obj);

    void amsg_envs_filled_push(amsg_envs_obj * obj, msg_envs_obj * msg_envs);

    msg_envs_obj * amsg_envs_empty_pop(amsg_envs_obj * obj);

    void amsg_envs_empty_push(amsg_envs_obj * obj, msg_envs_obj * msg_envs);

#endif