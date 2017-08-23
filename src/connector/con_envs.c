    
    #include "con_envs.h"

    con_envs_obj * con_envs_construct(const unsigned int nOuts, const msg_envs_cfg * msg_envs_config) {

        con_envs_obj * obj;
        unsigned int iOut;

        obj = (con_envs_obj *) malloc(sizeof(con_envs_obj));

        obj->nOuts = nOuts;

        obj->in = msg_envs_construct(msg_envs_config);

        obj->outs = (msg_envs_obj **) malloc(sizeof(msg_envs_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_envs_construct(msg_envs_config);
        }

        return obj;

    }

    void con_envs_destroy(con_envs_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_envs_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_envs_destroy(obj->in);

        free((void *) obj);

    }

    int con_envs_process(con_envs_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_envs_copy(obj->outs[iOut], obj->in);
        }

        if (msg_envs_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }