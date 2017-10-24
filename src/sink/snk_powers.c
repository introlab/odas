    
    #include "snk_powers.h"

    snk_powers_obj * snk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config) {

        snk_powers_obj * obj;

        obj = (snk_powers_obj *) malloc(sizeof(snk_powers_obj));

        obj->halfFrameSize = msg_powers_config->halfFrameSize;
        obj->nChannels = msg_powers_config->nChannels;
        obj->fS = msg_powers_config->fS;
        
        obj->format = format_clone(snk_powers_config->format);
        obj->interface = interface_clone(snk_powers_config->interface);

        switch (obj->format->type) {
            
            case format_binary_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in = (msg_powers_obj *) NULL;

        return obj;

    }

    void snk_powers_destroy(snk_powers_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_powers_connect(snk_powers_obj * obj, msg_powers_obj * in) {

        obj->in = in;

    }

    void snk_powers_disconnect(snk_powers_obj * obj) {

        obj->in = (msg_powers_obj *) NULL;

    }

    int snk_powers_open(snk_powers_obj * obj) {

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

    int snk_powers_close(snk_powers_obj * obj) {

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

    int snk_powers_process(snk_powers_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = snk_powers_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_powers_process_socket(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_powers_process_file(snk_powers_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        float samplePower;
        int rtnValue;

        if (obj->in->timeStamp != 0) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {
                
                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    samplePower = obj->in->envs->array[iChannel][iSample];

                    switch (obj->format->type) {
                        
                        case format_binary_float:

                            fwrite(&samplePower, sizeof(float), 1, obj->fp);

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

    int snk_powers_process_socket(snk_powers_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    snk_powers_cfg * snk_powers_cfg_construct(void) {

        snk_powers_cfg * cfg;

        cfg = (snk_powers_cfg *) malloc(sizeof(snk_powers_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_powers_cfg_destroy(snk_powers_cfg * snk_powers_config) {

        if (snk_powers_config->format != NULL) {
            format_destroy(snk_powers_config->format);
        }
        if (snk_powers_config->interface != NULL) {
            interface_destroy(snk_powers_config->interface);
        }

        free((void *) snk_powers_config);

    }