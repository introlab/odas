    
    #include "snk_spectra.h"

    snk_spectra_obj * snk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config) {

        snk_spectra_obj * obj;

        obj = (snk_spectra_obj *) malloc(sizeof(snk_spectra_obj));

        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->fS = msg_spectra_config->fS;
        
        obj->format = format_clone(snk_spectra_config->format);
        obj->interface = interface_clone(snk_spectra_config->interface);

        obj->in = (msg_spectra_obj *) NULL;

        return obj;

    }

    void snk_spectra_destroy(snk_spectra_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_spectra_connect(snk_spectra_obj * obj, msg_spectra_obj * in) {

        obj->in = in;

    }

    void snk_spectra_disconnect(snk_spectra_obj * obj) {

        obj->in = (msg_spectra_obj *) NULL;

    }

    int snk_spectra_open(snk_spectra_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                obj->fp = fopen(obj->interface->fileName, "wb");

            break;

            case interface_socket:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    int snk_spectra_close(snk_spectra_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                fclose(obj->fp);

            break;

            case interface_socket:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    int snk_spectra_process(snk_spectra_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = snk_spectra_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_spectra_process_socket(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_spectra_process_file(snk_spectra_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        float sampleReal;
        float sampleImag;
        int rtnValue;

        if (obj->in->timeStamp != 0) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {
                
                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    sampleReal = obj->in->freqs->array[iChannel][iSample*2+0];
                    sampleImag = obj->in->freqs->array[iChannel][iSample*2+1];

                    switch (obj->format->type) {
                        
                        case format_float:

                            fwrite(&sampleReal, sizeof(float), 1, obj->fp);
                            fwrite(&sampleImag, sizeof(float), 1, obj->fp);

                        break;

                    }

                }

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int snk_spectra_process_socket(snk_spectra_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    snk_spectra_cfg * snk_spectra_cfg_construct(void) {

        snk_spectra_cfg * cfg;

        cfg = (snk_spectra_cfg *) malloc(sizeof(snk_spectra_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_spectra_cfg_destroy(snk_spectra_cfg * snk_spectra_config) {

        if (snk_spectra_config->format != NULL) {
            format_destroy(snk_spectra_config->format);
        }
        if (snk_spectra_config->interface != NULL) {
            interface_destroy(snk_spectra_config->interface);
        }

        free((void *) snk_spectra_config);

    }