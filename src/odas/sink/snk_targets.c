    
    #include <sink/snk_targets.h>

    snk_targets_obj * snk_targets_construct(const snk_targets_cfg * snk_targets_config, const msg_targets_cfg * msg_targets_config) {

        snk_targets_obj * obj;

        obj = (snk_targets_obj *) malloc(sizeof(snk_targets_obj));

        obj->timeStamp = 0;

        obj->nTargets = msg_targets_config->nTargets;
        
        obj->server_id = 0;
        obj->connection_id = 0;                
        obj->port = snk_targets_config->port;

        obj->bufferSize = 4096;
        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);

        obj->in = (msg_targets_obj *) NULL;

        return obj;

    }

    void snk_targets_destroy(snk_targets_obj * obj) {

        free((void *) obj->buffer);
        free((void *) obj);

    }

    void snk_targets_connect(snk_targets_obj * obj, msg_targets_obj * in) {

        obj->in = in;

    }

    void snk_targets_disconnect(snk_targets_obj * obj) {

        obj->in = (msg_targets_obj *) NULL;

    }

    void snk_targets_open(snk_targets_obj * obj) {


        struct sockaddr_in server_address;

        if (obj->port != 0) {

            memset(&server_address, 0x00, sizeof(server_address));
            server_address.sin_family = AF_INET;
            server_address.sin_addr.s_addr = htonl(INADDR_ANY);
            server_address.sin_port = htons(obj->port);

            obj->server_id = socket(AF_INET, SOCK_STREAM, 0);

            bind(obj->server_id, (struct sockaddr *) &server_address, sizeof(server_address));
            listen(obj->server_id, 1);
            obj->connection_id = accept(obj->server_id, (struct sockaddr *) NULL, NULL);

        }

    }

    void snk_targets_close(snk_targets_obj * obj) {

        if (obj->port != 0) {

            close(obj->connection_id);
            close(obj->server_id);

            obj->server_id = 0;
            obj->connection_id = 0;

        }

    }

    int snk_targets_process(snk_targets_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            snk_targets_process_format(obj);
            snk_targets_process_interface(obj);

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_targets_process_interface(snk_targets_obj * obj) {

        if (obj->port != 0) {

            if (send(obj->connection_id, obj->buffer, strlen(obj->buffer), 0) < 0) {
                printf("Sink targets: Could not send message.\n");
                exit(EXIT_FAILURE);
            }  

        }

    }

    void snk_targets_process_format(snk_targets_obj * obj) {

        unsigned int iTarget;

        obj->buffer[0] = 0x00;

        sprintf(&(obj->buffer[strlen(obj->buffer)]),"{\n");
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    \"timeStamp\": %llu,\n",obj->in->timeStamp);
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    \"targets\": [\n");

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

            sprintf(&(obj->buffer[strlen(obj->buffer)]), "        { \"tag\": \"%s\", \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f }", 
                    obj->in->targets->tags[iTarget],
                    obj->in->targets->array[iTarget*3+0], 
                    obj->in->targets->array[iTarget*3+1], 
                    obj->in->targets->array[iTarget*3+2]);

            if (iTarget != (obj->nTargets - 1)) {

                sprintf(&(obj->buffer[strlen(obj->buffer)]),",");

            }

            sprintf(&(obj->buffer[strlen(obj->buffer)]),"\n");

        }
        
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    ]\n");
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"}\n");


    }

    snk_targets_cfg * snk_targets_cfg_construct(void) {

        snk_targets_cfg * cfg;

        cfg = (snk_targets_cfg *) malloc(sizeof(snk_targets_cfg));

        cfg->port = 0;

        return cfg;

    }

    void snk_targets_cfg_destroy(snk_targets_cfg * snk_targets_config) {

        free((void *) snk_targets_config);

    }