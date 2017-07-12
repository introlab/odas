    
    #include "src_tracks.h"

    src_tracks_obj * src_tracks_construct(const src_tracks_cfg * src_tracks_config, const msg_tracks_cfg * msg_tracks_config) {

        src_tracks_obj * obj;
        unsigned int nBytes;

        obj = (src_tracks_obj *) malloc(sizeof(src_tracks_obj));

        obj->timeStamp = 0;

        obj->nTracks = msg_tracks_config->nTracks;
        obj->fS = src_tracks_config->fS;
        
        obj->format = format_clone(src_tracks_config->format);
        obj->interface = interface_clone(src_tracks_config->interface);

        switch (obj->format->type) {
            
            case format_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->buffer = (float *) malloc(sizeof(float) * 3 * obj->nTracks);

        obj->out = (msg_tracks_obj *) NULL;
        
        return obj;

    }

    void src_tracks_destroy(src_tracks_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void src_tracks_connect(src_tracks_obj * obj, msg_tracks_obj * out) {

        obj->out = out;

    }

    void src_tracks_disconnect(src_tracks_obj * obj) {

        obj->out = (msg_tracks_obj *) NULL;

    }

    void src_tracks_open(src_tracks_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_tracks_open_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }   

    }

    void src_tracks_open_file(src_tracks_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "rb");

    }

    void src_tracks_close(src_tracks_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_tracks_close_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void src_tracks_close_file(src_tracks_obj * obj) {

        fclose(obj->fp);

    }

    int src_tracks_process(src_tracks_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = src_tracks_process_file(obj);

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

    int src_tracks_process_file(src_tracks_obj * obj) {

        unsigned int iTrack;
        int nSamples;
        int rtnValue;

        memset(obj->buffer, 0x00, sizeof(float) * 3 * obj->nTracks);
        nSamples = fread(obj->buffer, sizeof(float), 3 * obj->nTracks, obj->fp);

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            obj->out->tracks->array[iTrack*3+0] = obj->buffer[iTrack*3+0];
            obj->out->tracks->array[iTrack*3+1] = obj->buffer[iTrack*3+1];
            obj->out->tracks->array[iTrack*3+2] = obj->buffer[iTrack*3+2];

        }

        if (nSamples != (3 * obj->nTracks)) {
            
            rtnValue = -1;    

        }
        else {

            rtnValue = 0;

        }

        return rtnValue;

    }

    src_tracks_cfg * src_tracks_cfg_construct(void) {

        src_tracks_cfg * cfg;

        cfg = (src_tracks_cfg *) malloc(sizeof(src_tracks_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_tracks_cfg_destroy(src_tracks_cfg * src_tracks_config) {

        if (src_tracks_config->format != NULL) {
            format_destroy(src_tracks_config->format);
        }
        if (src_tracks_config->interface != NULL) {
            interface_destroy(src_tracks_config->interface);
        }

        free((void *) src_tracks_config);

    }