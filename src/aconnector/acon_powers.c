    
    #include "acon_powers.h"

    acon_powers_obj * acon_powers_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_powers_cfg * msg_powers_config) {

        acon_powers_obj * obj;
        unsigned int iOut;

        obj = (acon_powers_obj *) malloc(sizeof(acon_powers_obj));

        obj->in = amsg_powers_construct(nMessages, msg_powers_config);

        obj->outs = (amsg_powers_obj **) malloc(sizeof(amsg_powers_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_powers_construct(nMessages, msg_powers_config);
        }

        obj->con_powers = con_powers_construct(nOuts, msg_powers_config);

        obj->thread = thread_construct(&acon_powers_thread, (void *) obj);

        return obj;

    }

    void acon_powers_destroy(acon_powers_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_powers->nOuts;

        thread_destroy(obj->thread);

        con_powers_destroy(obj->con_powers);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_powers_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_powers_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_powers_thread(void * ptr) {

        msg_powers_obj * msg_powers_in;
        msg_powers_obj * msg_powers_out;

        acon_powers_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_powers_obj *) ptr;

        nOuts = obj->con_powers->nOuts;

        while(1) {

            msg_powers_in = amsg_powers_filled_pop(obj->in);
            msg_powers_copy(obj->con_powers->in, msg_powers_in);
            amsg_powers_empty_push(obj->in, msg_powers_in);

            rtnValue = con_powers_process(obj->con_powers);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_powers_out = amsg_powers_empty_pop(obj->outs[iOut]);
                msg_powers_copy(msg_powers_out, obj->con_powers->outs[iOut]);
                amsg_powers_filled_push(obj->outs[iOut], msg_powers_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }