#ifndef __ODAS_ACONNECTOR_TRACKS
#define __ODAS_ACONNECTOR_TRACKS

    #include "../connector/con_tracks.h"
    #include "../amessage/amsg_tracks.h"
    #include "../message/msg_tracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_tracks_obj {

        amsg_tracks_obj * in;
        amsg_tracks_obj ** outs;
        con_tracks_obj * con_tracks;
        thread_obj * thread;

    } acon_tracks_obj;

    acon_tracks_obj * acon_tracks_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config);

    void acon_tracks_destroy(acon_tracks_obj * obj);

    void * acon_tracks_thread(void * ptr);

#endif