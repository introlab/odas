#ifndef __ODAS_MESSAGE_HOPS
#define __ODAS_MESSAGE_HOPS

    #include <stdlib.h>
    #include "../signal/hop.h"
    #include "../utils/fifo.h"

    typedef struct msg_hops_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        hops_obj * hops;

    } msg_hops_obj;

    typedef struct msg_hops_cfg {

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_hops_cfg;

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * msg_hops_config);

    void msg_hops_destroy(msg_hops_obj * obj);

    void msg_hops_copy(msg_hops_obj * dest, const msg_hops_obj * src);

    void msg_hops_zero(msg_hops_obj * obj);

    unsigned int msg_hops_isZero(const msg_hops_obj * obj);

    msg_hops_cfg * msg_hops_cfg_construct(void);

    void msg_hops_cfg_destroy(msg_hops_cfg * msg_hops_config);

    void msg_hops_cfg_printf(const msg_hops_cfg * msg_hops_config);

#endif