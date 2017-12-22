#ifndef __ODAS_ASINK_POWERS
#define __ODAS_ASINK_POWERS

    #include "../amessage/amsg_powers.h"
    #include "../sink/snk_powers.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_powers_obj {

        snk_powers_obj * snk_powers;
        amsg_powers_obj * in;
        thread_obj * thread;

    } asnk_powers_obj;

    asnk_powers_obj * asnk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config);

    void asnk_powers_destroy(asnk_powers_obj * obj);

    void asnk_powers_connect(asnk_powers_obj * obj, amsg_powers_obj * in);

    void asnk_powers_disconnect(asnk_powers_obj * obj);

    void * asnk_powers_thread(void * ptr);

#endif