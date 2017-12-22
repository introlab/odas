    
    #include "asnk_powers.h"

    asnk_powers_obj * asnk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config) {

        asnk_powers_obj * obj;

        obj = (asnk_powers_obj *) malloc(sizeof(asnk_powers_obj));

        obj->snk_powers = snk_powers_construct(snk_powers_config, msg_powers_config);
        obj->in = (amsg_powers_obj *) NULL;

        obj->thread = thread_construct(&asnk_powers_thread, (void *) obj);

        return obj;

    }

    void asnk_powers_destroy(asnk_powers_obj * obj) {

        snk_powers_destroy(obj->snk_powers);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_powers_connect(asnk_powers_obj * obj, amsg_powers_obj * in) {

        obj->in = in;

    }

    void asnk_powers_disconnect(asnk_powers_obj * obj) {

        obj->in = (amsg_powers_obj *) NULL;

    }

    void * asnk_powers_thread(void * ptr) {

        asnk_powers_obj * obj;
        msg_powers_obj * msg_powers_in;
        int rtnValue;

        obj = (asnk_powers_obj *) ptr;

        // Open the sink
        snk_powers_open(obj->snk_powers);

        while(1) {

            // Pop a message, process, and push back
            msg_powers_in = amsg_powers_filled_pop(obj->in);
            snk_powers_connect(obj->snk_powers, msg_powers_in);
            rtnValue = snk_powers_process(obj->snk_powers);
            snk_powers_disconnect(obj->snk_powers);
            amsg_powers_empty_push(obj->in, msg_powers_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_powers_close(obj->snk_powers);

    }