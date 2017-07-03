#ifndef __ODAS_MESSAGE_POTS
#define __ODAS_MESSAGE_POTS

    #include <stdlib.h>
    #include "../signal/pot.h"

    typedef struct msg_pots_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        pots_obj * pots;

    } msg_pots_obj;

    typedef struct msg_pots_cfg {

        unsigned int nPots;
        unsigned int fS;

    } msg_pots_cfg;

    msg_pots_obj * msg_pots_construct(const msg_pots_cfg * cfg);

    void msg_pots_destroy(msg_pots_obj * obj);

    void msg_pots_copy(msg_pots_obj * dest, const msg_pots_obj * src);

    void msg_pots_zero(msg_pots_obj * obj);

    unsigned int msg_pots_isZero(const msg_pots_obj * obj);

    msg_pots_cfg * msg_pots_cfg_construct(void);

    void msg_pots_cfg_destroy(msg_pots_cfg * cfg);

    void msg_pots_cfg_printf(const msg_pots_cfg * msg_pots_config);

#endif