
    #include "msg_tracks.h"

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg) {

        msg_tracks_obj * obj;

        obj = (msg_tracks_obj *) malloc(sizeof(msg_tracks_obj));

        obj->timeStamp = 0;
        obj->fS = cfg->fS;
        obj->tracks = tracks_construct_zero(cfg->nTracks);

        return obj;

    }

    void msg_tracks_destroy(msg_tracks_obj * obj) {

        tracks_destroy(obj->tracks);
        free((void *) obj);

    }

    void msg_tracks_copy(msg_tracks_obj * dest, const msg_tracks_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        tracks_copy(dest->tracks, src->tracks);

    }

    void msg_tracks_zero(msg_tracks_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        tracks_zero(obj->tracks);

    }

    unsigned int msg_tracks_isZero(const msg_tracks_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_tracks_cfg * msg_tracks_cfg_construct(void) {

        msg_tracks_cfg * cfg;

        cfg = (msg_tracks_cfg *) malloc(sizeof(msg_tracks_cfg));

        cfg->nTracks = 0;

        return cfg;

    }

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg) {

        free((void *) cfg);

    }

    void msg_tracks_cfg_printf(const msg_tracks_cfg * msg_tracks_config) {

        printf("nTracks = %u\n", msg_tracks_config->nTracks);
        printf("fS = %u\n", msg_tracks_config->fS);        

    }    