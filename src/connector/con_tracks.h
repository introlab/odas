#ifndef __ODAS_CONNECTOR_TRACKS
#define __ODAS_CONNECTOR_TRACKS

    #include "../message/msg_tracks.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_tracks_obj {

        msg_tracks_obj * in;
        msg_tracks_obj ** outs;

        unsigned int nOuts;

    } con_tracks_obj;

    con_tracks_obj * con_tracks_construct(const unsigned int nOuts, const msg_tracks_cfg * msg_tracks_config);

    void con_tracks_destroy(con_tracks_obj * obj);

    int con_tracks_process(con_tracks_obj * obj);

#endif