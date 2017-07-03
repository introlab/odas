    
    #include "snk_hops.h"

    snk_hops_obj * snk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config) {

        snk_hops_obj * obj;

        obj = (snk_hops_obj *) malloc(sizeof(snk_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        obj->fS = snk_hops_config->fS;
        
        obj->format = format_clone(snk_hops_config->format);
        obj->interface = interface_clone(snk_hops_config->interface);

        memset(obj->bytes, 0x00, 4 * sizeof(char));

        obj->in = (msg_hops_obj *) NULL;

        return obj;

    }

    void snk_hops_destroy(snk_hops_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_hops_connect(snk_hops_obj * obj, msg_hops_obj * in) {

        obj->in = in;

    }

    void snk_hops_disconnect(snk_hops_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;

    }

    int snk_hops_open(snk_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                obj->fp = fopen(obj->interface->fileName, "wb");

            break;

            case interface_socket:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            case interface_soundcard:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    int snk_hops_close(snk_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                fclose(obj->fp);

            break;

            case interface_socket:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            case interface_soundcard:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    int snk_hops_process(snk_hops_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = snk_hops_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_hops_process_socket(obj);

            break;

            case interface_soundcard:

                rtnValue = snk_hops_process_soundcard(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_hops_process_file(snk_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        signed char sampleChar;
        signed short sampleShort;
        signed int sampleInt;
        float sample;
        int rtnValue;

        if (obj->in->timeStamp != 0) {

            for (iSample = 0; iSample < obj->hopSize; iSample++) {
                
                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    sample = obj->in->hops->array[iChannel][iSample];

                    switch (obj->format->type) {
                        
                        case format_bin08:

                            pcm_normalized2signed08bits(sample, obj->bytes);
                            fwrite(&(obj->bytes[3]), sizeof(char), 1, obj->fp);

                        break;

                        case format_bin16:

                            pcm_normalized2signed16bits(sample, obj->bytes);
                            fwrite(&(obj->bytes[2]), sizeof(char), 2, obj->fp);

                        break;

                        case format_bin24:

                            pcm_normalized2signed24bits(sample, obj->bytes);
                            fwrite(&(obj->bytes[1]), sizeof(char), 3, obj->fp);

                        break;
                        
                        case format_bin32:
                        
                            pcm_normalized2signed32bits(sample, obj->bytes);
                            fwrite(&(obj->bytes[0]), sizeof(char), 4, obj->fp);
                        
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

    int snk_hops_process_socket(snk_hops_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    int snk_hops_process_soundcard(snk_hops_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    snk_hops_cfg * snk_hops_cfg_construct(void) {

        snk_hops_cfg * cfg;

        cfg = (snk_hops_cfg *) malloc(sizeof(snk_hops_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_hops_cfg_destroy(snk_hops_cfg * snk_hops_config) {

        if (snk_hops_config->format != NULL) {
            format_destroy(snk_hops_config->format);
        }
        if (snk_hops_config->interface != NULL) {
            interface_destroy(snk_hops_config->interface);
        }

        free((void *) snk_hops_config);

    }