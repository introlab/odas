#ifndef __ODAS_ASINK_HOPSTRACKS
#define __ODAS_ASINK_HOPSTRACKS

    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_tracks.h"
    #include "../sink/snk_hopstracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_hopstracks_obj {

        snk_hopstracks_obj * snk_hopstracks;
        amsg_hops_obj * in1;
        amsg_tracks_obj * in2;
        thread_obj * thread;

    } asnk_hopstracks_obj;

    asnk_hopstracks_obj * asnk_hopstracks_construct(const snk_hopstracks_cfg * snk_hopstracks_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config);

    void asnk_hopstracks_destroy(asnk_hopstracks_obj * obj);

    void asnk_hopstracks_connect(asnk_hopstracks_obj * obj, amsg_hops_obj * in1, amsg_tracks_obj * in2);

    void asnk_hopstracks_disconnect(asnk_hopstracks_obj * obj);

    void * asnk_hopstracks_thread(void * ptr);

#endif