    
    #include "con_categories.h"

    con_categories_obj * con_categories_construct(const unsigned int nOuts, const msg_categories_cfg * msg_categories_config) {

        con_categories_obj * obj;
        unsigned int iOut;

        obj = (con_categories_obj *) malloc(sizeof(con_categories_obj));

        obj->nOuts = nOuts;

        obj->in = msg_categories_construct(msg_categories_config);

        obj->outs = (msg_categories_obj **) malloc(sizeof(msg_categories_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_categories_construct(msg_categories_config);
        }

        return obj;

    }

    void con_categories_destroy(con_categories_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_categories_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_categories_destroy(obj->in);

        free((void *) obj);

    }

    int con_categories_process(con_categories_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_categories_copy(obj->outs[iOut], obj->in);
        }

        if (msg_categories_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }