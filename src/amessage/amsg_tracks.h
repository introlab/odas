#ifndef __ODAS_AMESSAGE_TRACKS
#define __ODAS_AMESSAGE_TRACKS

    #include <stdlib.h>

    #include "../message/msg_tracks.h"
    #include "../utils/fifo.h"

    typedef struct amsg_tracks_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_tracks_obj;

    amsg_tracks_obj * amsg_tracks_construct(const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config);

    void amsg_tracks_destroy(amsg_tracks_obj * obj);

    msg_tracks_obj * amsg_tracks_filled_pop(amsg_tracks_obj * obj);

    void amsg_tracks_filled_push(amsg_tracks_obj * obj, msg_tracks_obj * msg_tracks);

    msg_tracks_obj * amsg_tracks_empty_pop(amsg_tracks_obj * obj);

    void amsg_tracks_empty_push(amsg_tracks_obj * obj, msg_tracks_obj * msg_tracks);

#endif