
    #include "con_targets.h"

    con_targets_obj * con_targets_construct(const unsigned int nOuts, const msg_targets_cfg * msg_targets_config) {

        con_targets_obj * obj;
        unsigned int iOut;

        obj = (con_targets_obj *) malloc(sizeof(con_targets_obj));

        obj->nOuts = nOuts;

        obj->in = msg_targets_construct(msg_targets_config);

        obj->outs = (msg_targets_obj **) malloc(sizeof(msg_targets_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_targets_construct(msg_targets_config);
        }

        return obj;    

    }

    void con_targets_destroy(con_targets_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_targets_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_targets_destroy(obj->in);

        free((void *) obj);

    }

    int con_targets_process(con_targets_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_targets_copy(obj->outs[iOut], obj->in);
        }

        if (msg_targets_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }