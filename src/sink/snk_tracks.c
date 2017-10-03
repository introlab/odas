    
    #include "snk_tracks.h"

    snk_tracks_obj * snk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config) {

        snk_tracks_obj * obj;

        obj = (snk_tracks_obj *) malloc(sizeof(snk_tracks_obj));

        obj->timeStamp = 0;

        obj->nTracks = msg_tracks_config->nTracks;
        obj->fS = snk_tracks_config->fS;
        
        obj->format = format_clone(snk_tracks_config->format);
        obj->interface = interface_clone(snk_tracks_config->interface);

        switch (obj->format->type) {
            
            case format_text_json: break;
            case format_binary_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->fp = (FILE *) NULL;

        obj->smessage = (char *) malloc(sizeof(char) * (1024 + 1024 * msg_tracks_config->nTracks));

        obj->in = (msg_tracks_obj *) NULL;

        return obj;

    }

    void snk_tracks_destroy(snk_tracks_obj * obj) {

        free((void *) obj->smessage);

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_tracks_connect(snk_tracks_obj * obj, msg_tracks_obj * in) {

        obj->in = in;

    }

    void snk_tracks_disconnect(snk_tracks_obj * obj) {

        obj->in = (msg_tracks_obj *) NULL;

    }

    int snk_tracks_open(snk_tracks_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                // Empty

            break;

            case interface_file:

                obj->fp = fopen(obj->interface->fileName, "wb");

            break;

            case interface_socket:

                memset(&(obj->sclient), 0x00, sizeof(struct sockaddr_in));

                obj->sclient.sin_family = AF_INET;
                obj->sclient.sin_addr.s_addr = inet_addr(obj->interface->ip);
                obj->sclient.sin_port = htons(obj->interface->port);
                obj->sid = socket(AF_INET, SOCK_STREAM, 0);

                if ( (connect(obj->sid, (struct sockaddr *) &(obj->sclient), sizeof(obj->sclient))) < 0 ) {

                    printf("Cannot connect to server\n");
                    exit(EXIT_FAILURE);

                }   

            break;

            case interface_terminal:

                // (Empty)

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    int snk_tracks_close(snk_tracks_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                // Empty

            break;

            case interface_file:

                fclose(obj->fp);

            break;

            case interface_socket:

                close(obj->sid);

            break;

            case interface_terminal:

                // Empty

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    int snk_tracks_process(snk_tracks_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_blackhole:

                rtnValue = snk_tracks_process_blackhole(obj);

            break;

            case interface_file:

                rtnValue = snk_tracks_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_tracks_process_socket(obj);

            break;

            case interface_terminal:

                rtnValue = snk_tracks_process_terminal(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_tracks_process_blackhole(snk_tracks_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;          

    }

    int snk_tracks_process_file(snk_tracks_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_binary_float:

                    fwrite(obj->in->tracks->ids, sizeof(unsigned long long), obj->in->tracks->nTracks, obj->fp);
                    fwrite(obj->in->tracks->array, sizeof(float), 3 * obj->in->tracks->nTracks, obj->fp);

                break;

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int snk_tracks_process_socket(snk_tracks_obj * obj) {

        int rtnValue;
        unsigned int iTrack;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_text_json:

                    obj->smessage[0] = 0x00;

                    sprintf(obj->smessage,"%s{\n",obj->smessage);
                    sprintf(obj->smessage,"%s    \"timeStamp\": %llu,\n",obj->smessage,obj->in->timeStamp);
                    sprintf(obj->smessage,"%s    \"src\": [\n",obj->smessage);

                    for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

                        sprintf(obj->smessage,"%s        { \"id\": %llu, \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f }", obj->smessage, 
                                obj->in->tracks->ids[iTrack],
                                obj->in->tracks->array[iTrack*3+0], 
                                obj->in->tracks->array[iTrack*3+1], 
                                obj->in->tracks->array[iTrack*3+2]);

                        if (iTrack != (obj->nTracks - 1)) {

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

    int snk_tracks_process_terminal(snk_tracks_obj * obj) {

        int rtnValue;
        unsigned int iTrack;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_text_json:

                    printf("{\n");
                    printf("    \"timeStamp\": %llu,\n",obj->in->timeStamp);
                    printf("    \"src\": [\n");

                    for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

                        printf("        { \"id\": %llu, \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f }",
                                obj->in->tracks->ids[iTrack],
                                obj->in->tracks->array[iTrack*3+0], obj->in->tracks->array[iTrack*3+1], obj->in->tracks->array[iTrack*3+2]);

                        if (iTrack != (obj->nTracks - 1)) {

                            printf(",");

                        }

                        printf("\n");

                    }
                    
                    printf("    ]\n");
                    printf("}\n");

                    rtnValue = 0;

                break;               

            }

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;        

    }

    snk_tracks_cfg * snk_tracks_cfg_construct(void) {

        snk_tracks_cfg * cfg;

        cfg = (snk_tracks_cfg *) malloc(sizeof(snk_tracks_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_tracks_cfg_destroy(snk_tracks_cfg * snk_tracks_config) {

        if (snk_tracks_config->format != NULL) {
            format_destroy(snk_tracks_config->format);
        }
        if (snk_tracks_config->interface != NULL) {
            interface_destroy(snk_tracks_config->interface);
        }

        free((void *) snk_tracks_config);

    }