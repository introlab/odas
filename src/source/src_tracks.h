#ifndef __ODAS_SOURCE_TRACKS
#define __ODAS_SOURCE_TRACKS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_tracks.h"
    #include "../signal/pot.h"
    #include "../utils/pcm.h"

    typedef struct src_tracks_obj {

        unsigned long long timeStamp;

        unsigned int nTracks;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        float * buffer;

        msg_tracks_obj * out;

    } src_tracks_obj;

    typedef struct src_tracks_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } src_tracks_cfg;

    src_tracks_obj * src_tracks_construct(const src_tracks_cfg * src_tracks_config, const msg_tracks_cfg * msg_tracks_config);

    void src_tracks_destroy(src_tracks_obj * obj);

    void src_tracks_connect(src_tracks_obj * obj, msg_tracks_obj * out);

    void src_tracks_disconnect(src_tracks_obj * obj);

    void src_tracks_open(src_tracks_obj * obj);

    void src_tracks_open_file(src_tracks_obj * obj);

    void src_tracks_close(src_tracks_obj * obj);

    void src_tracks_close_file(src_tracks_obj * obj);

    int src_tracks_process(src_tracks_obj * obj);

    int src_tracks_process_file(src_tracks_obj * obj);

    src_tracks_cfg * src_tracks_cfg_construct(void);

    void src_tracks_cfg_destroy(src_tracks_cfg * src_tracks_config);

#endif