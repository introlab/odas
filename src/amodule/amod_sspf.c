    
    #include "amod_sspf.h"

    amod_sspf_obj * amod_sspf_construct(const mod_sspf_cfg * mod_sspf_config, const msg_spectra_cfg * msg_spectra_config, const msg_tracks_cfg * msg_tracks_config) {

        amod_sspf_obj * obj;

        obj = (amod_sspf_obj *) malloc(sizeof(amod_sspf_obj));

        obj->mod_sspf = mod_sspf_construct(mod_sspf_config, msg_spectra_config, msg_tracks_config);

        obj->in1 = (amsg_spectra_obj *) NULL;
        obj->in2 = (amsg_spectra_obj *) NULL;
        obj->in3 = (amsg_tracks_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;
        
        obj->thread = thread_construct(&amod_sspf_thread, (void *) obj);

        return obj;

    }

    void amod_sspf_destroy(amod_sspf_obj * obj) {

        mod_sspf_destroy(obj->mod_sspf);
        thread_destroy(obj->thread);

        free((void *) obj); 

    }

    void amod_sspf_connect(amod_sspf_obj * obj, amsg_spectra_obj * in1, amsg_spectra_obj * in2, amsg_tracks_obj * in3, amsg_spectra_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->in3 = in3;
        obj->out = out;

    }

    void amod_sspf_disconnect(amod_sspf_obj * obj) {

        obj->in1 = (amsg_spectra_obj *) NULL;
        obj->in2 = (amsg_spectra_obj *) NULL;
        obj->in3 = (amsg_tracks_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

    }

    void * amod_sspf_thread(void * ptr) {

        amod_sspf_obj * obj;
        msg_spectra_obj * msg_spectra_in1;
        msg_spectra_obj * msg_spectra_in2;
        msg_tracks_obj * msg_tracks_in;
        msg_spectra_obj * msg_spectra_out;
        int rtnValue;

        obj = (amod_sspf_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in1 = amsg_spectra_filled_pop(obj->in1);
            msg_spectra_in2 = amsg_spectra_filled_pop(obj->in2);
            msg_tracks_in = amsg_tracks_filled_pop(obj->in3);
            msg_spectra_out = amsg_spectra_empty_pop(obj->out);
            mod_sspf_connect(obj->mod_sspf, msg_spectra_in1, msg_spectra_in2, msg_tracks_in, msg_spectra_out);
            rtnValue = mod_sspf_process(obj->mod_sspf);
            mod_sspf_disconnect(obj->mod_sspf);
            amsg_spectra_empty_push(obj->in1, msg_spectra_in1);
            amsg_spectra_empty_push(obj->in2, msg_spectra_in2);
            amsg_tracks_empty_push(obj->in3, msg_tracks_in);
            amsg_spectra_filled_push(obj->out, msg_spectra_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }