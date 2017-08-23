#ifndef __ODAS_MESSAGE_ENVS
#define __ODAS_MESSAGE_ENVS

    #include <stdlib.h>

    #include "../signal/env.h"

    typedef struct msg_envs_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        envs_obj * envs;

    } msg_envs_obj;

    typedef struct msg_envs_cfg {

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_envs_cfg;

    msg_envs_obj * msg_envs_construct(const msg_envs_cfg * msg_envs_config);

    void msg_envs_destroy(msg_envs_obj * obj);

    void msg_envs_copy(msg_envs_obj * dest, const msg_envs_obj * src);

    void msg_envs_zero(msg_envs_obj * obj);

    unsigned int msg_envs_isZero(const msg_envs_obj * obj);

    msg_envs_cfg * msg_envs_cfg_construct(void);

    void msg_envs_cfg_destroy(msg_envs_cfg * msg_envs_config);

    void msg_envs_cfg_printf(const msg_envs_cfg * msg_envs_config);

#endif