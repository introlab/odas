    
    #include "snk_tracks.h"

    snk_tracks_obj * snk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config) {

        snk_tracks_obj * obj;

        obj = (snk_tracks_obj *) malloc(sizeof(snk_tracks_obj));

        obj->timeStamp = 0;

        obj->nTracks = msg_tracks_config->nTracks;
        obj->fS = snk_tracks_config->fS;
        
        obj->format = format_clone(snk_tracks_config->format);
        obj->interface = interface_clone(snk_tracks_config->interface);

        obj->in = (msg_tracks_obj *) NULL;

        return obj;

    }

    void snk_tracks_destroy(snk_tracks_obj * obj) {

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

    int snk_tracks_close(snk_tracks_obj * obj) {

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

    int snk_tracks_process(snk_tracks_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = snk_tracks_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_tracks_process_socket(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_tracks_process_file(snk_tracks_obj * obj) {

        int rtnValue;
        //unsigned int iTrack;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_float:

                    fwrite(obj->in->tracks->ids, sizeof(unsigned long long), obj->in->tracks->nTracks, obj->fp);
                    fwrite(obj->in->tracks->array, sizeof(float), 3 * obj->in->tracks->nTracks, obj->fp);

                    /*for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {
                        printf("(%03llu): (%f,%f,%f)\n",obj->in->tracks->ids[iTrack],obj->in->tracks->array[iTrack*3+0],obj->in->tracks->array[iTrack*3+1],obj->in->tracks->array[iTrack*3+2]);
                    }
                    printf("\n");*/

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

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

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