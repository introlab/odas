    
    #include "amod_stft.h"

    amod_stft_obj * amod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config) {

        amod_stft_obj * obj;

        obj = (amod_stft_obj *) malloc(sizeof(amod_stft_obj));

        obj->mod_stft = mod_stft_construct(mod_stft_config, msg_hops_config, msg_spectra_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

        obj->thread = thread_construct(&amod_stft_thread, (void *) obj);

        return obj;

    }

    void amod_stft_destroy(amod_stft_obj * obj) {

        mod_stft_destroy(obj->mod_stft);
        thread_destroy(obj->thread);

        free((void *) obj);           

    }

    void amod_stft_connect(amod_stft_obj * obj, amsg_hops_obj * in, amsg_spectra_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_stft_disconnect(amod_stft_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

    }

    void * amod_stft_thread(void * ptr) {

        amod_stft_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_spectra_obj * msg_spectra_out;
        int rtnValue;

        obj = (amod_stft_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_spectra_out = amsg_spectra_empty_pop(obj->out);
            mod_stft_connect(obj->mod_stft, msg_hops_in, msg_spectra_out);
            rtnValue = mod_stft_process(obj->mod_stft);
            mod_stft_disconnect(obj->mod_stft);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_spectra_filled_push(obj->out, msg_spectra_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }