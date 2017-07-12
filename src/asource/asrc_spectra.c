    
    #include "asrc_spectra.h"

    asrc_spectra_obj * asrc_spectra_construct(const src_spectra_cfg * src_spectra_config, const msg_spectra_cfg * msg_spectra_config) {

        asrc_spectra_obj * obj;

        obj = (asrc_spectra_obj *) malloc(sizeof(asrc_spectra_obj));

        obj->src_spectra = src_spectra_construct(src_spectra_config, msg_spectra_config);
        obj->out = (amsg_spectra_obj *) NULL;

        obj->thread = thread_construct(&asrc_spectra_thread, (void *) obj);

        return obj;

    }

    void asrc_spectra_destroy(asrc_spectra_obj * obj) {

        src_spectra_destroy(obj->src_spectra);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asrc_spectra_connect(asrc_spectra_obj * obj, amsg_spectra_obj * out) {

        obj->out = out;

    }

    void asrc_spectra_disconnect(asrc_spectra_obj * obj) {

        obj->out = (amsg_spectra_obj *) NULL;

    }

    void * asrc_spectra_thread(void * ptr) {

        asrc_spectra_obj * obj;
        msg_spectra_obj * msg_spectra_out;
        int rtnValue;

        obj = (asrc_spectra_obj *) ptr;

        // Open the source
        src_spectra_open(obj->src_spectra);

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_out = amsg_spectra_empty_pop(obj->out);
            src_spectra_connect(obj->src_spectra, msg_spectra_out);
            rtnValue = src_spectra_process(obj->src_spectra);
            src_spectra_disconnect(obj->src_spectra);
            amsg_spectra_filled_push(obj->out, msg_spectra_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

            // Some other process may ask to stop the thread
            if (thread_askedToStop(obj->thread) == 1) {
                break;
            }

        }

        // Close the source
        src_spectra_close(obj->src_spectra);

        // Send the "0" message, that kills all connected threads
        // that will consume this message
        msg_spectra_out = amsg_spectra_empty_pop(obj->out);
        msg_spectra_zero(msg_spectra_out);
        amsg_spectra_filled_push(obj->out, msg_spectra_out);

    }