    
    #include "amod_resample.h"

    amod_resample_obj * amod_resample_construct(const mod_resample_cfg * mod_resample_config, const msg_hops_cfg * msg_hops_in_config, const msg_hops_cfg * msg_hops_out_config) {

        amod_resample_obj * obj;

        obj = (amod_resample_obj *) malloc(sizeof(amod_resample_obj));

        obj->mod_resample = mod_resample_construct(mod_resample_config, msg_hops_in_config, msg_hops_out_config);
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

        obj->thread = thread_construct(&amod_resample_thread, (void *) obj);

        return obj;

    }

    void amod_resample_destroy(amod_resample_obj * obj) {

        mod_resample_destroy(obj->mod_resample);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_resample_connect(amod_resample_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_resample_disconnect(amod_resample_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

    }

    void * amod_resample_thread(void * ptr) {

        amod_resample_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (amod_resample_obj *) ptr;

        rtnValue = 4;

        while(1) {
                        
            if ((rtnValue == 3) || (rtnValue == 4)) {
                msg_hops_in = amsg_hops_filled_pop(obj->in);   
            }
            if ((rtnValue == 2) || (rtnValue == 4)) {
                msg_hops_out = amsg_hops_empty_pop(obj->out);
            }          
                
            mod_resample_connect(obj->mod_resample, msg_hops_in, msg_hops_out);
            rtnValue = mod_resample_process(obj->mod_resample);
            mod_resample_disconnect(obj->mod_resample);

            if ((rtnValue == 3) || (rtnValue == 4) || (rtnValue == -1)) {
                amsg_hops_empty_push(obj->in, msg_hops_in);
            }
            if ((rtnValue == 2) || (rtnValue == 4) || (rtnValue == -1)) {
                amsg_hops_filled_push(obj->out, msg_hops_out);
            }

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }