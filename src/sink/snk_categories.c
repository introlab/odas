
   /**
    * \file     snk_categories.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <sink/snk_categories.h>

    snk_categories_obj * snk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config) {

        snk_categories_obj * obj;

        obj = (snk_categories_obj *) malloc(sizeof(snk_categories_obj));

        obj->timeStamp = 0;

        obj->nChannels = msg_categories_config->nChannels;
        obj->fS = snk_categories_config->fS;
        
        obj->format = format_clone(snk_categories_config->format);
        obj->interface = interface_clone(snk_categories_config->interface);

        if (!(((obj->interface->type == interface_blackhole)  && (obj->format->type == format_undefined)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_terminal) && (obj->format->type == format_text_json)))) {
            
            printf("Sink categories: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        obj->buffer = (char *) malloc(sizeof(char) * 1024);
        memset(obj->buffer, 0x00, sizeof(char) * 1024);
        obj->bufferSize = 0;

        obj->in = (msg_categories_obj *) NULL;

        return obj;

    }

    void snk_categories_destroy(snk_categories_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj->buffer);

        free((void *) obj);

    }

    void snk_categories_connect(snk_categories_obj * obj, msg_categories_obj * in) {

        obj->in = in;

    }

    void snk_categories_disconnect(snk_categories_obj * obj) {

        obj->in = (msg_categories_obj *) NULL;

    }

    void snk_categories_open(snk_categories_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_categories_open_interface_blackhole(obj);

            break;

            case interface_file:

                snk_categories_open_interface_file(obj);

            break;

            case interface_socket:

                snk_categories_open_interface_socket(obj);

            break;

            case interface_terminal:

                snk_categories_open_interface_terminal(obj);

            break;

            default:

                printf("Sink categories: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    void snk_categories_open_interface_blackhole(snk_categories_obj * obj) {

        // Empty

    }

    void snk_categories_open_interface_file(snk_categories_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "wb");

        if (obj->fp == NULL) {
            printf("Cannot open file %s\n",obj->interface->fileName);
            exit(EXIT_FAILURE);
        }        

    }

    void snk_categories_open_interface_socket(snk_categories_obj * obj) {

        memset(&(obj->sserver), 0x00, sizeof(struct sockaddr_in));

        obj->sserver.sin_family = AF_INET;
        obj->sserver.sin_addr.s_addr = inet_addr(obj->interface->ip);
        obj->sserver.sin_port = htons(obj->interface->port);
        obj->sid = socket(AF_INET, SOCK_STREAM, 0);

        if ( (connect(obj->sid, (struct sockaddr *) &(obj->sserver), sizeof(obj->sserver))) < 0 ) {

            printf("Sink categories: Cannot connect to server\n");
            exit(EXIT_FAILURE);

        }          

    }

    void snk_categories_open_interface_terminal(snk_categories_obj * obj) {

        // Empty

    }  

    void snk_categories_close(snk_categories_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_categories_close_interface_blackhole(obj);

            break;

            case interface_file:

                snk_categories_close_interface_file(obj);

            break;

            case interface_socket:

                snk_categories_close_interface_socket(obj);

            break;

            case interface_terminal:

                snk_categories_close_interface_terminal(obj);

            break;

            default:

                printf("Sink categories: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_categories_close_interface_blackhole(snk_categories_obj * obj) {

        // Empty

    }

    void snk_categories_close_interface_file(snk_categories_obj * obj) {

        fclose(obj->fp);

    }

    void snk_categories_close_interface_socket(snk_categories_obj * obj) {

        close(obj->sid);

    }

    void snk_categories_close_interface_terminal(snk_categories_obj * obj) {

        // Empty

    }

    int snk_categories_process(snk_categories_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_text_json:

                    snk_categories_process_format_text_json(obj);

                break;

                case format_undefined:                

                    snk_categories_process_format_undefined(obj);

                break;

                default:

                    printf("Sink categories: Invalid format type.\n");
                    exit(EXIT_FAILURE);

                break;

            }

            switch(obj->interface->type) {

                case interface_blackhole:

                    snk_categories_process_interface_blackhole(obj);

                break;  

                case interface_file:

                    snk_categories_process_interface_file(obj);

                break;

                case interface_socket:

                    snk_categories_process_interface_socket(obj);

                break;

                case interface_terminal:

                    snk_categories_process_interface_terminal(obj);

                break;

                default:

                    printf("Sink categories: Invalid interface type.\n");
                    exit(EXIT_FAILURE);

                break;

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_categories_process_interface_blackhole(snk_categories_obj * obj) {

        // Empty

    }

    void snk_categories_process_interface_file(snk_categories_obj * obj) {

        fwrite(obj->buffer, sizeof(char), obj->bufferSize, obj->fp);

    }

    void snk_categories_process_interface_socket(snk_categories_obj * obj) {

        if (send(obj->sid, obj->buffer, obj->bufferSize, 0) < 0) {
            printf("Sink categories: Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    void snk_categories_process_interface_terminal(snk_categories_obj * obj) {

        printf("%s",obj->buffer);

    }

    void snk_categories_process_format_text_json(snk_categories_obj * obj) {

        unsigned int iChannel;

        obj->buffer[0] = 0x00;

        sprintf(obj->buffer,"%s{\n",obj->buffer);
        sprintf(obj->buffer,"%s    \"timeStamp\": %llu,\n",obj->buffer,obj->in->timeStamp);
        sprintf(obj->buffer,"%s    \"src\": [\n",obj->buffer);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            switch(obj->in->categories->array[iChannel]) {

                case 0x01:

                    sprintf(obj->buffer,"%s        { \"category\": \"speech\" }",obj->buffer);

                break;

                case 0x00:

                    sprintf(obj->buffer,"%s        { \"category\": \"nonspeech\" }",obj->buffer);

                break;

                default:

                    sprintf(obj->buffer,"%s        { \"category\": \"undefined\" }",obj->buffer);

                break;

            }

            if (iChannel != (obj->nChannels - 1)) {

                sprintf(obj->buffer,"%s,",obj->buffer);

            }

            sprintf(obj->buffer,"%s\n",obj->buffer);

        }
        
        sprintf(obj->buffer,"%s    ]\n",obj->buffer);
        sprintf(obj->buffer,"%s}\n",obj->buffer);

        obj->bufferSize = strlen(obj->buffer);

    }

    void snk_categories_process_format_undefined(snk_categories_obj * obj) {

        obj->buffer[0] = 0x00;
        obj->bufferSize = 0;

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
