    
    #include "src_hops.h"

    src_hops_obj * src_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config) {

        src_hops_obj * obj;

        obj = (src_hops_obj *) malloc(sizeof(src_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        obj->fS = src_hops_config->fS;
        
        obj->format = format_clone(src_hops_config->format);
        obj->interface = interface_clone(src_hops_config->interface);

        memset(obj->bytes, 0x00, 4 * sizeof(char));

        obj->out = (msg_hops_obj *) NULL;
        
        return obj;

    }

    void src_hops_destroy(src_hops_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void src_hops_connect(src_hops_obj * obj, msg_hops_obj * out) {

        obj->out = out;

    }

    void src_hops_disconnect(src_hops_obj * obj) {

        obj->out = (msg_hops_obj *) NULL;

    }

    void src_hops_open(src_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                obj->fp = fopen(obj->interface->fileName, "rb");

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

    void src_hops_close(src_hops_obj * obj) {

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

    int src_hops_process(src_hops_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = src_hops_process_file(obj);

            break;

            case interface_socket:

                rtnValue = src_hops_process_socket(obj);

            break;

            case interface_soundcard:

                rtnValue = src_hops_process_soundcard(obj);

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

    int src_hops_process_file(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        signed char sampleChar;
        signed short sampleShort;
        signed int sampleInt;
        float sample;
        int rtnValue;
        int tmp;

        rtnValue = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {
            
            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            
                if (!feof(obj->fp)) {

                    switch (obj->format->type) {
                        
                        case format_bin08:

                            tmp = fread(&(obj->bytes[3]), sizeof(char), 1, obj->fp);
                            sample = pcm_signed08bits2normalized(obj->bytes);

                        break;

                        case format_bin16:
    
                            tmp = fread(&(obj->bytes[2]), sizeof(char), 2, obj->fp);
                            sample = pcm_signed16bits2normalized(obj->bytes);

                        break;

                        case format_bin24:

                            tmp = fread(&(obj->bytes[1]), sizeof(char), 3, obj->fp);
                            sample = pcm_signed24bits2normalized(obj->bytes);

                        break;
                        
                        case format_bin32:
                        
                            tmp = fread(&(obj->bytes[0]), sizeof(char), 4, obj->fp);
                            sample = pcm_signed32bits2normalized(obj->bytes);
                        
                        break;
                    }

                }
                else {

                    sample = 0.0f;
                    rtnValue = -1;

                }

                obj->out->hops->array[iChannel][iSample] = sample;

            }

        }

        return rtnValue;

    }

    int src_hops_process_socket(src_hops_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    int src_hops_process_soundcard(src_hops_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    src_hops_cfg * src_hops_cfg_construct(void) {

        src_hops_cfg * cfg;

        cfg = (src_hops_cfg *) malloc(sizeof(src_hops_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_hops_cfg_destroy(src_hops_cfg * src_hops_config) {

        if (src_hops_config->format != NULL) {
            format_destroy(src_hops_config->format);
        }
        if (src_hops_config->interface != NULL) {
            interface_destroy(src_hops_config->interface);
        }

        free((void *) src_hops_config);

    }
