    
    #include "amod_ssl.h"

    amod_ssl_obj * amod_ssl_construct(const mod_ssl_cfg * mod_ssl_config, const msg_spectra_cfg * msg_spectra_config, const msg_pots_cfg * msg_pots_config) {

        amod_ssl_obj * obj;

        obj = (amod_ssl_obj *) malloc(sizeof(amod_ssl_obj));

        obj->mod_ssl = mod_ssl_construct(mod_ssl_config, msg_spectra_config, msg_pots_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_pots_obj *) NULL;

        obj->thread = thread_construct(&amod_ssl_thread, (void *) obj);

        return obj;

    }

    void amod_ssl_destroy(amod_ssl_obj * obj) {

        mod_ssl_destroy(obj->mod_ssl);
        thread_destroy(obj->thread);

        free((void *) obj); 

    }

    void amod_ssl_connect(amod_ssl_obj * obj, amsg_spectra_obj * in, amsg_pots_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_ssl_disconnect(amod_ssl_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_pots_obj *) NULL;

    }

    void * amod_ssl_thread(void * ptr) {

        amod_ssl_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_pots_obj * msg_pots_out;
        int rtnValue;

        obj = (amod_ssl_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_pots_out = amsg_pots_empty_pop(obj->out);
            mod_ssl_connect(obj->mod_ssl, msg_spectra_in, msg_pots_out);
            rtnValue = mod_ssl_process(obj->mod_ssl);
            mod_ssl_disconnect(obj->mod_ssl);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_pots_filled_push(obj->out, msg_pots_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }


        }

    }
