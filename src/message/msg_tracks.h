#ifndef __ODAS_MESSAGE_TRACKS
#define __ODAS_MESSAGE_TRACKS

    #include <stdlib.h>
    #include "../signal/track.h"

    typedef struct msg_tracks_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        tracks_obj * tracks;

    } msg_tracks_obj;

    typedef struct msg_tracks_cfg {

        unsigned int nTracks;
        unsigned int fS;

    } msg_tracks_cfg;

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg);

    void msg_tracks_destroy(msg_tracks_obj * obj);

    void msg_tracks_copy(msg_tracks_obj * dest, const msg_tracks_obj * src);

    void msg_tracks_zero(msg_tracks_obj * obj);

    unsigned int msg_tracks_isZero(const msg_tracks_obj * obj);

    msg_tracks_cfg * msg_tracks_cfg_construct(void);

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg);

    void msg_tracks_cfg_printf(const msg_tracks_cfg * msg_tracks_config);

#endif