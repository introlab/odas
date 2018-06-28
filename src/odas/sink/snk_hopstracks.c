    
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

        obj->nBytes = 2;
        obj->nSamples = obj->hopSize * obj->nChannels;       
        obj->bufferSize = obj->hopSize * (obj->nChannels + 1) * obj->nBytes;

        obj->bufferInterleave = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->bufferInterleave, 0x00, sizeof(char) * obj->bufferSize);
        obj->bufferPerChannel = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->bufferPerChannel, 0x00, sizeof(char) * obj->bufferSize);
        obj->buffer = (float *) malloc(sizeof(float) * obj->nSamples);
        memset(obj->buffer, 0x00, sizeof(float) * obj->nSamples);

        obj->in1 = (msg_hops_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;

        return obj;

    }

    void snk_hopstracks_destroy(snk_hopstracks_obj * obj) {

        free((void *) obj->bufferPerChannel);
        free((void *) obj->bufferInterleave);
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

            if (send(obj->connection_id, obj->bufferInterleave, obj->bufferSize, 0) < 0) {
                printf("Sink hops: Could not send message.\n");
                exit(EXIT_FAILURE);           
            }

        }

    }

    void snk_hopstracks_process_format(snk_hopstracks_obj * obj) {

        unsigned int iChannel;
        unsigned int iElement;
        unsigned int nBytes;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            memcpy(&(obj->buffer[iChannel * obj->hopSize]), obj->in1->hops->array[iChannel], obj->hopSize * sizeof(float));
        }        

        pcm_normalized2SXle(obj->bufferPerChannel, obj->buffer, obj->nBytes, obj->nSamples);

        nBytes = obj->nSamples * obj->nBytes;
        memset(&(obj->bufferPerChannel[nBytes]), 0xFF, sizeof(unsigned long long));
        nBytes += sizeof(unsigned long long);
        memcpy(&(obj->bufferPerChannel[nBytes]), &(obj->in1->timeStamp), sizeof(unsigned long long));
        nBytes += sizeof(unsigned long long);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            memcpy(&(obj->bufferPerChannel[nBytes]), &(obj->in2->tracks->ids[iChannel]), sizeof(unsigned long long));
            nBytes += sizeof(unsigned long long);

            for (iElement = 0; iElement < 3; iElement++) {

                memcpy(&(obj->bufferPerChannel[nBytes]), &(obj->in2->tracks->array[iChannel*3+iElement]), sizeof(float));
                nBytes += sizeof(float);

            }

        }
        
        interleave_perchannel2interleave(obj->bufferInterleave, obj->bufferPerChannel, obj->nBytes, obj->nChannels + 1, obj->hopSize);       

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