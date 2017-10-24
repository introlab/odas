    
    #include "amod_classify.h"

    amod_classify_obj * amod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_categories_cfg * msg_categories_config) {

        amod_classify_obj * obj;

        obj = (amod_classify_obj *) malloc(sizeof(amod_classify_obj));

        obj->mod_classify = mod_classify_construct(mod_classify_config, msg_hops_config, msg_categories_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_categories_obj *) NULL;        

        obj->thread = thread_construct(&amod_classify_thread, (void *) obj);

        return obj;

    }

    void amod_classify_destroy(amod_classify_obj * obj) {

        mod_classify_destroy(obj->mod_classify);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_classify_connect(amod_classify_obj * obj, amsg_hops_obj * in, amsg_categories_obj * out) {

        obj->in = in;
        obj->out = out;        

    }

    void amod_classify_disconnect(amod_classify_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_categories_obj *) NULL;

    }

    void * amod_classify_thread(void * ptr) {

        amod_classify_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_categories_obj * msg_categories_out;
        int rtnValue;

        obj = (amod_classify_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_categories_out = amsg_categories_empty_pop(obj->out);
            mod_classify_connect(obj->mod_classify, msg_hops_in, msg_categories_out);
            rtnValue = mod_classify_process(obj->mod_classify);
            mod_classify_disconnect(obj->mod_classify);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_categories_filled_push(obj->out, msg_categories_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
