    
    #include "src_spectra.h"

    src_spectra_obj * src_spectra_construct(const src_spectra_cfg * src_spectra_config, const msg_spectra_cfg * msg_spectra_config) {

        src_spectra_obj * obj;
        unsigned int nBytes;

        obj = (src_spectra_obj *) malloc(sizeof(src_spectra_obj));

        obj->timeStamp = 0;

        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->nChannels = msg_spectra_config->nChannels;
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

    void src_spectra_destroy(src_spectra_obj * obj) {

        free((void *) obj->buffer);
        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void src_spectra_connect(src_spectra_obj * obj, msg_spectra_obj * out) {

        obj->out = out;

    }

    void src_spectra_disconnect(src_spectra_obj * obj) {

        obj->out = (msg_spectra_obj *) NULL;

    }

    void src_spectra_open(src_spectra_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_spectra_open_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }   

    }

    void src_spectra_open_file(src_spectra_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "rb");

    }

    void src_spectra_close(src_spectra_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_spectra_close_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void src_spectra_close_file(src_spectra_obj * obj) {

        fclose(obj->fp);

    }

    int src_spectra_process(src_spectra_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = src_spectra_process_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

        obj->timeStamp++;
        obj->out->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    int src_spectra_process_file(src_spectra_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        float sampleReal;
        float sampleImag;
        int nSamples;
        int rtnValue;

        memset(obj->buffer, 0x00, sizeof(float) * obj->halfFrameSize * 2 * obj->nChannels);
        nSamples = fread(obj->buffer, sizeof(float), obj->halfFrameSize * 2 * obj->nChannels, obj->fp);

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                obj->out->freqs->array[iChannel][iSample*2+0] = obj->buffer[(iSample*2) * obj->nChannels + iChannel + 0];
                obj->out->freqs->array[iChannel][iSample*2+1] = obj->buffer[(iSample*2) * obj->nChannels + iChannel + 1];

            }

        }

        if (nSamples != (obj->nChannels * obj->halfFrameSize)) {
            
            rtnValue = -1;    

        }
        else {

            rtnValue = 0;

        }

        return rtnValue;

    }

    src_spectra_cfg * src_spectra_cfg_construct(void) {

        src_spectra_cfg * cfg;

        cfg = (src_spectra_cfg *) malloc(sizeof(src_spectra_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_spectra_cfg_destroy(src_spectra_cfg * src_spectra_config) {

        if (src_spectra_config->format != NULL) {
            format_destroy(src_spectra_config->format);
        }
        if (src_spectra_config->interface != NULL) {
            interface_destroy(src_spectra_config->interface);
        }

        free((void *) src_spectra_config);

    }