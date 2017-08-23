    
    #include "acon_envs.h"

    acon_envs_obj * acon_envs_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_envs_cfg * msg_envs_config) {

        acon_envs_obj * obj;
        unsigned int iOut;

        obj = (acon_envs_obj *) malloc(sizeof(acon_envs_obj));

        obj->in = amsg_envs_construct(nMessages, msg_envs_config);

        obj->outs = (amsg_envs_obj **) malloc(sizeof(amsg_envs_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_envs_construct(nMessages, msg_envs_config);
        }

        obj->con_envs = con_envs_construct(nOuts, msg_envs_config);

        obj->thread = thread_construct(&acon_envs_thread, (void *) obj);

        return obj;

    }

    void acon_envs_destroy(acon_envs_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_envs->nOuts;

        thread_destroy(obj->thread);

        con_envs_destroy(obj->con_envs);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_envs_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_envs_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_envs_thread(void * ptr) {

        msg_envs_obj * msg_envs_in;
        msg_envs_obj * msg_envs_out;

        acon_envs_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_envs_obj *) ptr;

        nOuts = obj->con_envs->nOuts;

        while(1) {

            msg_envs_in = amsg_envs_filled_pop(obj->in);
            msg_envs_copy(obj->con_envs->in, msg_envs_in);
            amsg_envs_empty_push(obj->in, msg_envs_in);

            rtnValue = con_envs_process(obj->con_envs);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_envs_out = amsg_envs_empty_pop(obj->outs[iOut]);
                msg_envs_copy(msg_envs_out, obj->con_envs->outs[iOut]);
                amsg_envs_filled_push(obj->outs[iOut], msg_envs_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }