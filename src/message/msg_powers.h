#ifndef __ODAS_MESSAGE_POWERS
#define __ODAS_MESSAGE_POWERS

    #include <stdlib.h>

    #include "../signal/env.h"

    typedef struct msg_powers_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        envs_obj * envs;

    } msg_powers_obj;

    typedef struct msg_powers_cfg {

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_powers_cfg;

    msg_powers_obj * msg_powers_construct(const msg_powers_cfg * msg_powers_config);

    void msg_powers_destroy(msg_powers_obj * obj);

    void msg_powers_copy(msg_powers_obj * dest, const msg_powers_obj * src);

    void msg_powers_zero(msg_powers_obj * obj);

    unsigned int msg_powers_isZero(const msg_powers_obj * obj);

    msg_powers_cfg * msg_powers_cfg_construct(void);

    void msg_powers_cfg_destroy(msg_powers_cfg * msg_powers_config);

    void msg_powers_cfg_printf(const msg_powers_cfg * msg_powers_config);

#endif