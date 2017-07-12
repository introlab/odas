    
    #include "src_xcorrs.h"

    src_xcorrs_obj * src_xcorrs_construct(const src_xcorrs_cfg * src_xcorrs_config, const msg_xcorrs_cfg * msg_xcorrs_config) {

        src_xcorrs_obj * obj;
        unsigned int nBytes;

        obj = (src_xcorrs_obj *) malloc(sizeof(src_xcorrs_obj));

        obj->timeStamp = 0;

        obj->frameSize = msg_spectra_config->frameSize;
        obj->nPairs = msg_spectra_config->nPairs;
        obj->fS = src_spectra_config->fS;
        
        obj->format = format_clone(src_spectra_config->format);
        obj->interface = interface_clone(src_spectra_config->interface);

        switch (obj->format->type) {
            
            case format_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->buffer = (float *) malloc(sizeof(float) * obj->halfFrameSize * 2 * obj->nChannels);

        obj->out = (msg_spectra_obj *) NULL;
        
        return obj;

    }

    void src_xcorrs_destroy(src_xcorrs_obj * obj) {

    }

    void src_xcorrs_connect(src_xcorrs_obj * obj, msg_xcorrs_obj * out) {

    }

    void src_xcorrs_disconnect(src_xcorrs_obj * obj) {

    }

    void src_xcorrs_open(src_xcorrs_obj * obj) {

    }

    void src_xcorrs_open_file(src_xcorrs_obj * obj) {

    }

    void src_xcorrs_close(src_xcorrs_obj * obj) {

    }

    void src_xcorrs_close_file(src_xcorrs_obj * obj) {

    }

    int src_xcorrs_process(src_xcorrs_obj * obj) {

    }

    int src_xcorrs_process_file(src_xcorrs_obj * obj) {

    }

    src_xcorrs_cfg * src_xcorrs_cfg_construct(void) {

        src_xcorrs_cfg * cfg;

        cfg = (src_xcorrs_cfg *) malloc(sizeof(src_xcorrs_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_xcorrs_cfg_destroy(src_xcorrs_cfg * src_xcorrs_config) {

        if (src_xcorrs_config->format != NULL) {
            format_destroy(src_xcorrs_config->format);
        }
        if (src_xcorrs_config->interface != NULL) {
            interface_destroy(src_xcorrs_config->interface);
        }

        free((void *) src_xcorrs_config);

    }