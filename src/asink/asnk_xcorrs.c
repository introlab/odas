    
    #include "asnk_xcorrs.h"

    asnk_xcorrs_obj * asnk_xcorrs_construct(const snk_xcorrs_cfg * snk_xcorrs_config, const msg_xcorrs_cfg * msg_xcorrs_config) {

        asnk_xcorrs_obj * obj;

        obj = (asnk_xcorrs_obj *) malloc(sizeof(asnk_xcorrs_obj));

        obj->snk_spectra = snk_xcorrs_construct(snk_xcorrs_config, msg_xcorrs_config);
        obj->in = (amsg_xcorrs_obj *) NULL;

        obj->thread = thread_construct(&asnk_xcorrs_thread, (void *) obj);

        return obj;

    }

    void asnk_xcorrs_destroy(asnk_xcorrs_obj * obj) {

        snk_xcorrs_destroy(obj->snk_spectra);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_xcorrs_connect(asnk_xcorrs_obj * obj, amsg_xcorrs_obj * in) {

        obj->in = in;

    }

    void asnk_xcorrs_disconnect(asnk_xcorrs_obj * obj) {

        obj->in = (amsg_xcorrs_obj *) NULL;

    }

    void * asnk_xcorrs_thread(void * ptr) {

        asnk_xcorrs_obj * obj;
        msg_xcorrs_obj * msg_xcorrs_in;
        int rtnValue;

        obj = (asnk_xcorrs_obj *) ptr;

        // Open the sink
        snk_xcorrs_open(obj->snk_spectra);

        while(1) {

            // Pop a message, process, and push back
            msg_xcorrs_in = amsg_xcorrs_filled_pop(obj->in);
            snk_xcorrs_connect(obj->snk_spectra, msg_xcorrs_in);
            rtnValue = snk_xcorrs_process(obj->snk_spectra);
            snk_xcorrs_disconnect(obj->snk_spectra);
            amsg_xcorrs_empty_push(obj->in, msg_xcorrs_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_xcorrs_close(obj->snk_spectra);

    }