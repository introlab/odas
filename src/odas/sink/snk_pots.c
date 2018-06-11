   
   /**
    * \file     snk_pots.c
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
    
    #include <sink/snk_pots.h>

    snk_pots_obj * snk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config) {

        snk_pots_obj * obj;

        obj = (snk_pots_obj *) malloc(sizeof(snk_pots_obj));

        obj->timeStamp = 0;

        obj->nPots = msg_pots_config->nPots;
        obj->fS = snk_pots_config->fS;
        
        obj->format = format_clone(snk_pots_config->format);
        obj->interface = interface_clone(snk_pots_config->interface);

        if (!(((obj->interface->type == interface_blackhole)  && (obj->format->type == format_undefined)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_float)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_socket)  && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_terminal) && (obj->format->type == format_text_json)))) {
            
            printf("Sink pots: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        obj->fp = (FILE *) NULL;

        obj->buffer = (char *) malloc(sizeof(char) * 1024);
        memset(obj->buffer, 0x00, sizeof(char) * 1024);
        obj->bufferSize = 0;

        obj->in = (msg_pots_obj *) NULL;

        return obj;

    }

    void snk_pots_destroy(snk_pots_obj * obj) {

        free((void *) obj->buffer);

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

    void snk_pots_open(snk_pots_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_pots_open_interface_blackhole(obj);

            break;

            case interface_file:

                snk_pots_open_interface_file(obj);

            break;

            case interface_socket:
        
                snk_pots_open_interface_socket(obj);

            break;

            case interface_terminal:

                snk_pots_open_interface_terminal(obj);

            break;

            default:

                printf("Sink pots: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    void snk_pots_open_interface_blackhole(snk_pots_obj * obj) {

        // Empty

    }

    void snk_pots_open_interface_file(snk_pots_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "wb");

        if (obj->fp == NULL) {
            printf("Cannot open file %s\n",obj->interface->fileName);
            exit(EXIT_FAILURE);
        }

    }

    void snk_pots_open_interface_socket(snk_pots_obj * obj) {

        memset(&(obj->sserver), 0x00, sizeof(struct sockaddr_in));

        obj->sserver.sin_family = AF_INET;
        obj->sserver.sin_addr.s_addr = inet_addr(obj->interface->ip);
        obj->sserver.sin_port = htons(obj->interface->port);
        obj->sid = socket(AF_INET, SOCK_STREAM, 0);

        if ( (connect(obj->sid, (struct sockaddr *) &(obj->sserver), sizeof(obj->sserver))) < 0 ) {

            printf("Sink pots: Cannot connect to server\n");
            exit(EXIT_FAILURE);

        }  

    }

    void snk_pots_open_interface_terminal(snk_pots_obj * obj) {

        // Empty

    }

    void snk_pots_close(snk_pots_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_pots_close_interface_blackhole(obj);

            break;

            case interface_file:

                snk_pots_close_interface_file(obj);

            break;

            case interface_socket:

                snk_pots_close_interface_socket(obj);
                
            break;

            case interface_terminal:

                snk_pots_close_interface_terminal(obj);

            break;

            default:

                printf("Sink pots: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_pots_close_interface_blackhole(snk_pots_obj * obj) {

        // Empty

    }

    void snk_pots_close_interface_file(snk_pots_obj * obj) {

        fclose(obj->fp);

    }

    void snk_pots_close_interface_socket(snk_pots_obj * obj) {

        close(obj->sid);

    }

    void snk_pots_close_interface_terminal(snk_pots_obj * obj) {

        // Empty

    }

    int snk_pots_process(snk_pots_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_binary_float:

                    snk_pots_process_format_binary_float(obj);

                break;

                case format_text_json:

                    snk_pots_process_format_text_json(obj);

                break;

                case format_undefined:                

                    snk_pots_process_format_undefined(obj);

                break;

                default:

                    printf("Sink pots: Invalid format type.\n");
                    exit(EXIT_FAILURE);

                break;                

            }

            switch(obj->interface->type) {

                case interface_blackhole:

                    snk_pots_process_interface_blackhole(obj);

                break;

                case interface_file:

                    snk_pots_process_interface_file(obj);

                break;

                case interface_socket:

                    snk_pots_process_interface_socket(obj);

                break;

                case interface_terminal:

                    snk_pots_process_interface_terminal(obj);

                break;

                default:

                    printf("Sink pots: Invalid interface type.\n");
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

    void snk_pots_process_interface_blackhole(snk_pots_obj * obj) {

        // Empty

    }

    void snk_pots_process_interface_file(snk_pots_obj * obj) {

        fwrite(obj->buffer, sizeof(char), obj->bufferSize, obj->fp);

    }

    void snk_pots_process_interface_socket(snk_pots_obj * obj) {

        if (send(obj->sid, obj->buffer, obj->bufferSize, 0) < 0) {
            printf("Sink pots: Could not send message.\n");
            exit(EXIT_FAILURE);
        }        

    }

    void snk_pots_process_interface_terminal(snk_pots_obj * obj) {

        printf("%s",obj->buffer);

    }

    void snk_pots_process_format_binary_float(snk_pots_obj * obj) {

        memcpy(obj->buffer, obj->in->pots->array, sizeof(float) * 4 * obj->in->pots->nPots);
        obj->bufferSize = sizeof(float) * 4 * obj->in->pots->nPots;        

    }

    void snk_pots_process_format_text_json(snk_pots_obj * obj) {

        unsigned int iPot;

        obj->buffer[0] = 0x00;

        sprintf(obj->buffer,"%s{\n",obj->buffer);
        sprintf(obj->buffer,"%s    \"timeStamp\": %llu,\n",obj->buffer,obj->in->timeStamp);
        sprintf(obj->buffer,"%s    \"src\": [\n",obj->buffer);

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            sprintf(obj->buffer,"%s        { \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f, \"E\": %1.3f }", obj->buffer, 
                    obj->in->pots->array[iPot*4+0], obj->in->pots->array[iPot*4+1], obj->in->pots->array[iPot*4+2], obj->in->pots->array[iPot*4+3]);

            if (iPot != (obj->nPots - 1)) {

                sprintf(obj->buffer,"%s,",obj->buffer);

            }

            sprintf(obj->buffer,"%s\n",obj->buffer);

        }
        
        sprintf(obj->buffer,"%s    ]\n",obj->buffer);
        sprintf(obj->buffer,"%s}\n",obj->buffer);        

        obj->bufferSize = strlen(obj->buffer);

    }

    void snk_pots_process_format_undefined(snk_pots_obj * obj) {

        obj->buffer[0] = 0x00;
        obj->bufferSize = 0;        

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
