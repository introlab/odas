    
    #include "con_powers.h"

    con_powers_obj * con_powers_construct(const unsigned int nOuts, const msg_powers_cfg * msg_powers_config) {

        con_powers_obj * obj;
        unsigned int iOut;

        obj = (con_powers_obj *) malloc(sizeof(con_powers_obj));

        obj->nOuts = nOuts;

        obj->in = msg_powers_construct(msg_powers_config);

        obj->outs = (msg_powers_obj **) malloc(sizeof(msg_powers_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_powers_construct(msg_powers_config);
        }

        return obj;

    }

    void con_powers_destroy(con_powers_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_powers_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_powers_destroy(obj->in);

        free((void *) obj);

    }

    int con_powers_process(con_powers_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_powers_copy(obj->outs[iOut], obj->in);
        }

        if (msg_powers_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }