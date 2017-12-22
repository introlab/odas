#ifndef __ODAS_ASINK_TRACKS
#define __ODAS_ASINK_TRACKS

    #include "../amessage/amsg_tracks.h"
    #include "../sink/snk_tracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_tracks_obj {

        snk_tracks_obj * snk_tracks;
        amsg_tracks_obj * in;
        thread_obj * thread;

    } asnk_tracks_obj;

    asnk_tracks_obj * asnk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config);

    void asnk_tracks_destroy(asnk_tracks_obj * obj);

    void asnk_tracks_connect(asnk_tracks_obj * obj, amsg_tracks_obj * in);

    void asnk_tracks_disconnect(asnk_tracks_obj * obj);

    void * asnk_tracks_thread(void * ptr);

#endif