    
    #include "snk_xcorrs.h"

    snk_xcorrs_obj * snk_xcorrs_construct(const snk_xcorrs_cfg * snk_xcorrs_config, const msg_xcorrs_cfg * msg_xcorrs_config) {

        snk_xcorrs_obj * obj;

        obj = (snk_xcorrs_obj *) malloc(sizeof(snk_xcorrs_obj));

        obj->frameSize = msg_xcorrs_config->frameSize;
        obj->nPairs = msg_xcorrs_config->nPairs;
        obj->fS = msg_xcorrs_config->fS;
        
        obj->format = format_clone(snk_xcorrs_config->format);
        obj->interface = interface_clone(snk_xcorrs_config->interface);

        switch (obj->format->type) {
            
            case format_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in = (msg_xcorrs_obj *) NULL;

        return obj;

    }

    void snk_xcorrs_destroy(snk_xcorrs_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_xcorrs_connect(snk_xcorrs_obj * obj, msg_xcorrs_obj * in) {

        obj->in = in;

    }

    void snk_xcorrs_disconnect(snk_xcorrs_obj * obj) {

        obj->in = (msg_xcorrs_obj *) NULL;

    }

    int snk_xcorrs_open(snk_xcorrs_obj * obj) {

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

    int snk_xcorrs_close(snk_xcorrs_obj * obj) {

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

    int snk_xcorrs_process(snk_xcorrs_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = snk_xcorrs_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_xcorrs_process_socket(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_xcorrs_process_file(snk_xcorrs_obj * obj) {

        unsigned int iSample;
        unsigned int iPair;
        float sample;
        float sampleImag;
        int rtnValue;

        if (obj->in->timeStamp != 0) {

            for (iSample = 0; iSample < obj->frameSize; iSample++) {
                
                for (iPair = 0; iPair < obj->nPairs; iPair++) {

                    sample = obj->in->xcorrs->array[iPair][iSample];

                    switch (obj->format->type) {
                        
                        case format_float:

                            fwrite(&sample, sizeof(float), 1, obj->fp);

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

    int snk_xcorrs_process_socket(snk_xcorrs_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    snk_xcorrs_cfg * snk_xcorrs_cfg_construct(void) {

        snk_xcorrs_cfg * cfg;

        cfg = (snk_xcorrs_cfg *) malloc(sizeof(snk_xcorrs_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_xcorrs_cfg_destroy(snk_xcorrs_cfg * snk_xcorrs_config) {

        if (snk_xcorrs_config->format != NULL) {
            format_destroy(snk_xcorrs_config->format);
        }
        if (snk_xcorrs_config->interface != NULL) {
            interface_destroy(snk_xcorrs_config->interface);
        }

        free((void *) snk_xcorrs_config);

    }