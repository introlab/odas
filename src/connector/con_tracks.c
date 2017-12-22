    
    #include "con_tracks.h"

    con_tracks_obj * con_tracks_construct(const unsigned int nOuts, const msg_tracks_cfg * msg_tracks_config) {

        con_tracks_obj * obj;
        unsigned int iOut;

        obj = (con_tracks_obj *) malloc(sizeof(con_tracks_obj));

        obj->nOuts = nOuts;

        obj->in = msg_tracks_construct(msg_tracks_config);

        obj->outs = (msg_tracks_obj **) malloc(sizeof(msg_tracks_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_tracks_construct(msg_tracks_config);
        }

        return obj;        

    }

    void con_tracks_destroy(con_tracks_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_tracks_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_tracks_destroy(obj->in);

        free((void *) obj);

    }

    int con_tracks_process(con_tracks_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_tracks_copy(obj->outs[iOut], obj->in);
        }

        if (msg_tracks_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }