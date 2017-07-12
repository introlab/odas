    
    #include "src_pots.h"

    src_pots_obj * src_pots_construct(const src_pots_cfg * src_pots_config, const msg_pots_cfg * msg_pots_config) {

        src_pots_obj * obj;
        unsigned int nBytes;

        obj = (src_pots_obj *) malloc(sizeof(src_pots_obj));

        obj->timeStamp = 0;

        obj->nPots = msg_pots_config->nPots;
        obj->fS = src_pots_config->fS;
        
        obj->format = format_clone(src_pots_config->format);
        obj->interface = interface_clone(src_pots_config->interface);

        switch (obj->format->type) {
            
            case format_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->buffer = (float *) malloc(sizeof(float) * 4 * obj->nPots);

        obj->out = (msg_pots_obj *) NULL;
        
        return obj;

    }

    void src_pots_destroy(src_pots_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void src_pots_connect(src_pots_obj * obj, msg_pots_obj * out) {

        obj->out = out;

    }

    void src_pots_disconnect(src_pots_obj * obj) {

        obj->out = (msg_pots_obj *) NULL;

    }

    void src_pots_open(src_pots_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_pots_open_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }   

    }

    void src_pots_open_file(src_pots_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "rb");

    }

    void src_pots_close(src_pots_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_pots_close_file(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void src_pots_close_file(src_pots_obj * obj) {

        fclose(obj->fp);

    }

    int src_pots_process(src_pots_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = src_pots_process_file(obj);

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

    int src_pots_process_file(src_pots_obj * obj) {

        unsigned int iPot;
        int nSamples;
        int rtnValue;

        memset(obj->buffer, 0x00, sizeof(float) * 4 * obj->nPots);
        nSamples = fread(obj->buffer, sizeof(float), 4 * obj->nPots, obj->fp);

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            obj->out->pots->array[iPot*4+0] = obj->buffer[iPot*4+0];
            obj->out->pots->array[iPot*4+1] = obj->buffer[iPot*4+1];
            obj->out->pots->array[iPot*4+2] = obj->buffer[iPot*4+2];
            obj->out->pots->array[iPot*4+3] = obj->buffer[iPot*4+3];

        }

        if (nSamples != (4 * obj->nPots)) {
            
            rtnValue = -1;    

        }
        else {

            rtnValue = 0;

        }

        return rtnValue;

    }

    src_pots_cfg * src_pots_cfg_construct(void) {

        src_pots_cfg * cfg;

        cfg = (src_pots_cfg *) malloc(sizeof(src_pots_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_pots_cfg_destroy(src_pots_cfg * src_pots_config) {

        if (src_pots_config->format != NULL) {
            format_destroy(src_pots_config->format);
        }
        if (src_pots_config->interface != NULL) {
            interface_destroy(src_pots_config->interface);
        }

        free((void *) src_pots_config);

    }