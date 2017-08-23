    
    #include "amod_gain.h"

    amod_gain_obj * amod_gain_construct(const mod_gain_cfg * mod_gain_config, const msg_hops_cfg * msg_hops_config) {

        amod_gain_obj * obj;

        obj = (amod_gain_obj *) malloc(sizeof(amod_gain_obj));

        obj->mod_gain = mod_gain_construct(mod_gain_config, msg_hops_config);
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;        

        obj->thread = thread_construct(&amod_gain_thread, (void *) obj);

        return obj;

    }

    void amod_gain_destroy(amod_gain_obj * obj) {

        mod_gain_destroy(obj->mod_gain);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_gain_connect(amod_gain_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_gain_disconnect(amod_gain_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;     

    }

    void * amod_gain_thread(void * ptr) {

        amod_gain_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (amod_gain_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_hops_out = amsg_hops_empty_pop(obj->out);
            mod_gain_connect(obj->mod_gain, msg_hops_in, msg_hops_out);
            rtnValue = mod_gain_process(obj->mod_gain);
            mod_gain_disconnect(obj->mod_gain);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_hops_filled_push(obj->out, msg_hops_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }