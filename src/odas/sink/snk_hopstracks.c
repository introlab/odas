    
    #include <sink/snk_hopstracks.h>

    snk_hopstracks_obj * snk_hopstracks_construct(const snk_hopstracks_cfg * snk_hopstracks_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config) {

        snk_hopstracks_obj * obj;

        obj = (snk_hopstracks_obj *) malloc(sizeof(snk_hopstracks_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        
        obj->server_id = 0;
        obj->connection_id = 0;
        obj->port = snk_hopstracks_config->port;        

        memset(obj->bytes, 0x00, 4 * sizeof(char));

        obj->bufferOneChSize = obj->hopSize * 2;
        obj->bufferOneCh = (char *) malloc(sizeof(char) * obj->bufferOneChSize);
        memset(obj->bufferOneCh, 0x00, sizeof(char) * obj->bufferOneChSize);

        obj->bufferSize = obj->hopSize * obj->nChannels * 2 * 2;
        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);

        obj->in1 = (msg_hops_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;

        return obj;

    }

    void snk_hopstracks_destroy(snk_hopstracks_obj * obj) {

        free((void *) obj->bufferOneCh);
        free((void *) obj->buffer);
        free((void *) obj);        

    }

    void snk_hopstracks_connect(snk_hopstracks_obj * obj, msg_hops_obj * in1, msg_tracks_obj * in2) {

        obj->in1 = in1;
        obj->in2 = in2;

    }

    void snk_hopstracks_disconnect(snk_hopstracks_obj * obj) {

        obj->in1 = (msg_hops_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;

    }

    void snk_hopstracks_open(snk_hopstracks_obj * obj) {

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

    void snk_hopstracks_close(snk_hopstracks_obj * obj) {

        if (obj->port != 0) {

            close(obj->connection_id);
            close(obj->server_id);

            obj->server_id = 0;
            obj->connection_id = 0;

        }

    }

    int snk_hopstracks_process(snk_hopstracks_obj * obj) {

        int rtnValue;

        if (obj->in1->timeStamp != obj->in2->timeStamp) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (obj->in1->timeStamp != 0) {

            snk_hopstracks_process_format(obj);
            snk_hopstracks_process_interface(obj);

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_hopstracks_process_interface(snk_hopstracks_obj * obj) {

        if (obj->port != 0) {

            if (send(obj->connection_id, obj->buffer, obj->bufferSize, 0) < 0) {
                printf("Sink hops: Could not send message.\n");
                exit(EXIT_FAILURE);           
            }

        }

    }

    void snk_hopstracks_process_format(snk_hopstracks_obj * obj) {

        unsigned int iChannel;
        unsigned int iSample;
        float sample;
        unsigned int nBytes;
        unsigned int nBytesTotal;
        unsigned int ptrBytes;

        nBytes = 2;
        nBytesTotal = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                sample = obj->in1->hops->array[iChannel][iSample];
                pcm_normalized2signedXXbits(sample, nBytes, obj->bytes);
                memcpy(&(obj->buffer[nBytesTotal]), &(obj->bytes[4-nBytes]), sizeof(char) * nBytes);

                nBytesTotal += 2 * nBytes;

            }

        }

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            memset(obj->bufferOneCh, 0x00, sizeof(char) * obj->bufferOneChSize);

            sprintf(obj->bufferOneCh, "{\"id\":%llu,\"tag\":\"%s\",\"x\":%1.3f,\"y\":%1.3f,\"z\":%1.3f,\"activity\": %1.3f}", 
                    obj->in2->tracks->ids[iChannel],
                    obj->in2->tracks->tags[iChannel],
                    obj->in2->tracks->array[iChannel*3+0], 
                    obj->in2->tracks->array[iChannel*3+1], 
                    obj->in2->tracks->array[iChannel*3+2],
                    obj->in2->tracks->activity[iChannel]);

            nBytesTotal = iChannel * nBytes * 2 + nBytes;

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                memcpy(&(obj->buffer[nBytesTotal]), &(obj->bufferOneCh[iSample*nBytes]), nBytes * sizeof(char));

                nBytesTotal += obj->nChannels * nBytes * 2;

            }

        }       

    }

    snk_hopstracks_cfg * snk_hopstracks_cfg_construct(void) {

        snk_hopstracks_cfg * cfg;

        cfg = (snk_hopstracks_cfg *) malloc(sizeof(snk_hopstracks_cfg));

        cfg->port = 0;

        return cfg;

    }

    void snk_hopstracks_cfg_destroy(snk_hopstracks_cfg * snk_hopstracks_config) {

        free((void *) snk_hopstracks_config);

    }