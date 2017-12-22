    
    #include "con_pots.h"

    con_pots_obj * con_pots_construct(const unsigned int nOuts, const msg_pots_cfg * msg_pots_config) {

        con_pots_obj * obj;
        unsigned int iOut;

        obj = (con_pots_obj *) malloc(sizeof(con_pots_obj));

        obj->nOuts = nOuts;

        obj->in = msg_pots_construct(msg_pots_config);

        obj->outs = (msg_pots_obj **) malloc(sizeof(msg_pots_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_pots_construct(msg_pots_config);
        }

        return obj;

    }

    void con_pots_destroy(con_pots_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_pots_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_pots_destroy(obj->in);

        free((void *) obj);

    }

    int con_pots_process(con_pots_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_pots_copy(obj->outs[iOut], obj->in);
        }

        if (msg_pots_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }