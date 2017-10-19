    
    #include "snk_categories.h"

    snk_categories_obj * snk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config) {

        snk_categories_obj * obj;

        obj = (snk_categories_obj *) malloc(sizeof(snk_categories_obj));

        obj->timeStamp = 0;

        obj->nChannels = msg_categories_config->nChannels;
        obj->fS = snk_categories_config->fS;
        
        obj->format = format_clone(snk_categories_config->format);
        obj->interface = interface_clone(snk_categories_config->interface);

        switch (obj->format->type) {
            
            case format_text_json: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in = (msg_categories_obj *) NULL;

        return obj;

    }

    void snk_categories_destroy(snk_categories_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_categories_connect(snk_categories_obj * obj, msg_categories_obj * in) {

        obj->in = in;

    }

    void snk_categories_disconnect(snk_categories_obj * obj) {

        obj->in = (msg_categories_obj *) NULL;

    }

    int snk_categories_open(snk_categories_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                // Empty

            break;

            case interface_file:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            case interface_socket:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

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

    int snk_categories_close(snk_categories_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                // Empty

            break;

            case interface_file:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

            break;

            case interface_socket:

                printf("Not implemented yet.\n");
                exit(EXIT_FAILURE);

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

    int snk_categories_process(snk_categories_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_blackhole:

                rtnValue = snk_categories_process_blackhole(obj);

            break;  

            case interface_file:

                rtnValue = snk_categories_process_file(obj);

            break;

            case interface_socket:

                rtnValue = snk_categories_process_socket(obj);

            break;

            case interface_terminal:

                rtnValue = snk_categories_process_terminal(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int snk_categories_process_blackhole(snk_categories_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int snk_categories_process_file(snk_categories_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    int snk_categories_process_socket(snk_categories_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    int snk_categories_process_terminal(snk_categories_obj * obj) {



    }

    snk_categories_cfg * snk_categories_cfg_construct(void) {

        snk_categories_cfg * cfg;

        cfg = (snk_categories_cfg *) malloc(sizeof(snk_categories_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_categories_cfg_destroy(snk_categories_cfg * snk_categories_config) {

        if (snk_categories_config->format != NULL) {
            format_destroy(snk_categories_config->format);
        }
        if (snk_categories_config->interface != NULL) {
            interface_destroy(snk_categories_config->interface);
        }

        free((void *) snk_categories_config);

    }