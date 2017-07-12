#ifndef __ODAS_ASINK_XCORRS
#define __ODAS_ASINK_XCORRS

    #include "../amessage/amsg_xcorrs.h"
    #include "../sink/snk_xcorrs.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_xcorrs_obj {

        snk_xcorrs_obj * snk_xcorrs;
        amsg_xcorrs_obj * in;
        thread_obj * thread;

    } asnk_xcorrs_obj;

    asnk_xcorrs_obj * asnk_xcorrs_construct(const snk_xcorrs_cfg * snk_xcorrs_config, const msg_xcorrs_cfg * msg_xcorrs_config);

    void asnk_xcorrs_destroy(asnk_xcorrs_obj * obj);

    void asnk_xcorrs_connect(asnk_xcorrs_obj * obj, amsg_xcorrs_obj * in);

    void asnk_xcorrs_disconnect(asnk_xcorrs_obj * obj);

    void * asnk_xcorrs_thread(void * ptr);

#endif