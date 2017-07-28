    
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

        switch (obj->format->type) {
            
            case format_bin08: break;
            case format_bin16: break;
            case format_bin24: break;
            case format_bin32: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

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

                //struct sockaddr_in sserver;
                //char * smessage;
                //int sid;

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
        unsigned int nBytes;
        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch (obj->format->type) {

                case format_bin08: nBytes = 1; break;
                case format_bin16: nBytes = 2; break;
                case format_bin24: nBytes = 3; break;
                case format_bin32: nBytes = 4; break;

            }

            for (iSample = 0; iSample < obj->hopSize; iSample++) {
                
                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    sample = obj->in->hops->array[iChannel][iSample];
                    pcm_normalized2signedXXbits(sample, nBytes, obj->bytes);
                    fwrite(&(obj->bytes[4-nBytes]), sizeof(char), nBytes, obj->fp);

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