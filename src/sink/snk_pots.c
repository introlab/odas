    
    #include "snk_pots.h"

    snk_pots_obj * snk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config) {

        snk_pots_obj * obj;

        obj = (snk_pots_obj *) malloc(sizeof(snk_pots_obj));

        obj->timeStamp = 0;

        obj->nPots = msg_pots_config->nPots;
        obj->fS = snk_pots_config->fS;
        
        obj->format = format_clone(snk_pots_config->format);
        obj->interface = interface_clone(snk_pots_config->interface);

        switch (obj->format->type) {
            
            case format_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->fp = (FILE *) NULL;

        obj->smessage = (char *) malloc(sizeof(char) * (1024 + 1024 * msg_pots_config->nPots));

        obj->in = (msg_pots_obj *) NULL;

        return obj;

    }

    void snk_pots_destroy(snk_pots_obj * obj) {

        free((void *) obj->smessage);

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_pots_connect(snk_pots_obj * obj, msg_pots_obj * in) {

        obj->in = in;

    }

    void snk_pots_disconnect(snk_pots_obj * obj) {

        obj->in = (msg_pots_obj *) NULL;

    }

    int snk_pots_open(snk_pots_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                obj->fp = fopen(obj->interface->fileName, "wb");

            break;

            case interface_socket:
        
                obj->sclient.sin_family = AF_INET;
                obj->sclient.sin_port = htons(obj->interface->port);
                obj->sid = socket(AF_INET, SOCK_STREAM, 0);

                if ( (connect(obj->sid, (struct sockaddr *) &(obj->sclient), sizeof(obj->sclient))) < 0 ) {

                    printf("Cannot connect to server\n");
                    exit(EXIT_FAILURE);

                }                

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    int snk_pots_close(snk_pots_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                fclose(obj->fp);

            break;

            case interface_socket:

                close(obj->sid);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    int snk_pots_process(snk_pots_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = snk_pots_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_pots_process_socket(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_pots_process_file(snk_pots_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_float:

                    fwrite(obj->in->pots->array, sizeof(float), 4 * obj->in->pots->nPots, obj->fp);

                break;

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int snk_pots_process_socket(snk_pots_obj * obj) {

        int rtnValue;
        unsigned int iPot;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_float:

                    obj->smessage[0] = 0x00;

                    sprintf(obj->smessage,"%s{\n",obj->smessage);
                    sprintf(obj->smessage,"%s    \"timeStamp\": %llu,\n",obj->smessage,obj->in->timeStamp);
                    sprintf(obj->smessage,"%s    \"src\": [\n",obj->smessage);

                    for (iPot = 0; iPot < obj->nPots; iPot++) {

                        sprintf(obj->smessage,"%s        { x = %+1.3f, y = %+1.3f, z = %+1.3f, E = %+1.3f }", obj->smessage, 
                                obj->in->pots->array[iPot*4+0], obj->in->pots->array[iPot*4+1], obj->in->pots->array[iPot*4+2], obj->in->pots->array[iPot*4+3]);

                        if (iPot != (obj->nPots - 1)) {

                            sprintf(obj->smessage,"%s,",obj->smessage);

                        }

                        sprintf(obj->smessage,"%s\n",obj->smessage);

                    }
                    
                    sprintf(obj->smessage,"%s    ]\n",obj->smessage);
                    sprintf(obj->smessage,"%s}\n",obj->smessage);

                    if (send(obj->sid, obj->smessage, strlen(obj->smessage), 0) < 0) {
                        printf("Could not send message.\n");
                        exit(EXIT_FAILURE);
                    }

                    rtnValue = 0;

                break;               

            }

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    snk_pots_cfg * snk_pots_cfg_construct(void) {

        snk_pots_cfg * cfg;

        cfg = (snk_pots_cfg *) malloc(sizeof(snk_pots_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_pots_cfg_destroy(snk_pots_cfg * snk_pots_config) {

        if (snk_pots_config->format != NULL) {
            format_destroy(snk_pots_config->format);
        }
        if (snk_pots_config->interface != NULL) {
            interface_destroy(snk_pots_config->interface);
        }

        free((void *) snk_pots_config);

    }