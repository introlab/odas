#ifndef __ODAS_MESSAGE_TARGETS
#define __ODAS_MESSAGE_TARGETS

    #include <stdlib.h>
    #include "../signal/target.h"

    typedef struct msg_targets_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        targets_obj * targets;

    } msg_targets_obj;

    typedef struct msg_targets_cfg {

        unsigned int nTargets;
        unsigned int fS;

    } msg_targets_cfg;

    msg_targets_obj * msg_targets_construct(const msg_targets_cfg * cfg);

    void msg_targets_destroy(msg_targets_obj * obj);

    void msg_targets_copy(msg_targets_obj * dest, const msg_targets_obj * src);

    void msg_targets_zero(msg_targets_obj * obj);

    unsigned int msg_targets_isZero(const msg_targets_obj * obj);

    msg_targets_cfg * msg_targets_cfg_construct(void);

    void msg_targets_cfg_destroy(msg_targets_cfg * cfg);

    void msg_targets_cfg_printf(const msg_targets_cfg * msg_targets_config);

#endif