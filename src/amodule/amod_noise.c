    
    #include "amod_noise.h"

    amod_noise_obj * amod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config) {

        amod_noise_obj * obj;

        obj = (amod_noise_obj *) malloc(sizeof(amod_noise_obj));

        obj->mod_noise = mod_noise_construct(mod_noise_config, msg_spectra_config, msg_powers_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_powers_obj *) NULL;

        obj->thread = thread_construct(&amod_noise_thread, (void *) obj);

        return obj;


    }

    void amod_noise_destroy(amod_noise_obj * obj) {

        mod_noise_destroy(obj->mod_noise);
        thread_destroy(obj->thread);

        free((void *) obj);     

    }

    void amod_noise_connect(amod_noise_obj * obj, amsg_spectra_obj * in, amsg_powers_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_noise_disconnect(amod_noise_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_powers_obj *) NULL;

    }

    void * amod_noise_thread(void * ptr) {

        amod_noise_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_powers_obj * msg_powers_out;
        int rtnValue;

        obj = (amod_noise_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_powers_out = amsg_powers_empty_pop(obj->out);
            mod_noise_connect(obj->mod_noise, msg_spectra_in, msg_powers_out);
            rtnValue = mod_noise_process(obj->mod_noise);
            mod_noise_disconnect(obj->mod_noise);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_powers_filled_push(obj->out, msg_powers_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }