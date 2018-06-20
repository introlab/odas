   
   /**
    * \file     src_targets.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.1
    * \date     2018-06-12
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
    
    #include <source/src_targets.h>

    src_targets_obj * src_targets_construct(const src_targets_cfg * src_targets_config, const msg_targets_cfg * msg_targets_config) {

        src_targets_obj * obj;

        obj = (src_targets_obj *) malloc(sizeof(src_targets_obj));

        obj->timeStamp = 0;

        obj->nTargets = msg_targets_config->nTargets;
        obj->fS = msg_targets_config->fS;
        
        obj->format = format_clone(src_targets_config->format);
        obj->interface = interface_clone(src_targets_config->interface);

        obj->fp = (FILE *) NULL;
        obj->server_id = 0;
        obj->connection_id = 0;        

        if (!(((obj->interface->type == interface_blackhole)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_text_json)))) {
            
            printf("Source targets: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        obj->bufferSize = 4096;

        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);
        obj->string = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->string, 0x00, sizeof(char) * obj->bufferSize);

        obj->tokens = json_tokens_construct(1024);

        obj->targetsCst = targets_clone(src_targets_config->targets);

        obj->out = (msg_targets_obj *) NULL;
        
        return obj;

    }

    void src_targets_destroy(src_targets_obj * obj) {

        targets_destroy(obj->targetsCst);
        json_tokens_destroy(obj->tokens);
        free((void *) obj->buffer);
        free((void *) obj->string);
        format_destroy(obj->format);
        interface_destroy(obj->interface);       

        free((void *) obj);        

    }

    void src_targets_connect(src_targets_obj * obj, msg_targets_obj * out) {

        obj->out = out;

    }

    void src_targets_disconnect(src_targets_obj * obj) {

        obj->out = (msg_targets_obj *) NULL;

    }

    void src_targets_open(src_targets_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                src_targets_open_interface_blackhole(obj);

            break;

            case interface_file:

                src_targets_open_interface_file(obj);

            break;

            case interface_socket:

                src_targets_open_interface_socket(obj);

            break;

            default:

                printf("Source targets: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }        


    }

    void src_targets_open_interface_blackhole(src_targets_obj * obj) {

        // Nothing to do

    }

    void src_targets_open_interface_file(src_targets_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "rb");

        if (obj->fp == NULL) {
            printf("Cannot open file %s\n",obj->interface->fileName);
            exit(EXIT_FAILURE);
        }

    }

    void src_targets_open_interface_socket(src_targets_obj * obj) {

        struct sockaddr_in server_address;

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(obj->interface->port);

        obj->server_id = socket(AF_INET, SOCK_STREAM, 0);

        bind(obj->server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        listen(obj->server_id, 1);
        obj->connection_id = accept(obj->server_id, (struct sockaddr *) NULL, NULL);

    }

    void src_targets_close(src_targets_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                src_targets_close_interface_blackhole(obj);

            break;

            case interface_file:

                src_targets_close_interface_file(obj);

            break;

            case interface_socket:

                src_targets_close_interface_socket(obj);

            break;

            default:

                printf("Source targets: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void src_targets_close_interface_blackhole(src_targets_obj * obj) {

        // Nothing to do

    }

    void src_targets_close_interface_file(src_targets_obj * obj) {

        fclose(obj->fp);

    }

    void src_targets_close_interface_socket(src_targets_obj * obj) {

        close(obj->connection_id);
        close(obj->server_id);

        obj->server_id = 0;
        obj->connection_id = 0;

    }
    
    int src_targets_process(src_targets_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_blackhole:

                rtnValue = src_targets_process_interface_blackhole(obj);

            break;

            case interface_file:

                rtnValue = src_targets_process_interface_file(obj);

            break;

            case interface_socket:

                rtnValue = src_targets_process_interface_socket(obj);

            break;

            default:

                printf("Source targets: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

        switch(obj->format->type) {

            case format_text_json:

                src_targets_process_format_text_json(obj);

            break;

            default:

                printf("Source targets: Invalid format type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->timeStamp++;
        obj->out->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    int src_targets_process_interface_blackhole(src_targets_obj * obj) {

        obj->buffer[0] = 0x00;
        strcat(obj->buffer, "{\"targets\":[]}");

        strcpy(obj->string, obj->buffer);

        return 0;

    }

    int src_targets_process_interface_file(src_targets_obj * obj) {

        unsigned int nBytes;
        unsigned int messageSize;
        int ptr;
        int rtnValue;

        nBytes = strlen(obj->buffer);

        messageSize = fread(obj->buffer, obj->bufferSize - nBytes, sizeof(char), obj->fp);

        nBytes += messageSize;

        json_tokens_clear(obj->tokens);
        ptr = json_tokens_parse(obj->tokens, obj->buffer);

        if (ptr != -1) {

            memcpy(obj->string, obj->buffer, ptr);
            memmove(obj->buffer, &(obj->buffer[ptr]), nBytes - ptr);
            obj->buffer[nBytes - ptr] = 0x00;

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int src_targets_process_interface_socket(src_targets_obj * obj) {
        
        unsigned int nBytes;
        unsigned int messageSize;
        int ptr;

        nBytes = strlen(obj->buffer);

        while( (messageSize = recv(obj->connection_id, &(obj->buffer[nBytes]), (obj->bufferSize-nBytes), 0)) > 0) {

            nBytes += messageSize;

            json_tokens_clear(obj->tokens);
            ptr = json_tokens_parse(obj->tokens, obj->buffer);

            if (ptr != -1) {
                break;
            }

        }

        memcpy(obj->string, obj->buffer, ptr);
        memmove(obj->buffer, &(obj->buffer[ptr]), nBytes - ptr);
        obj->buffer[nBytes - ptr] = 0x00;

    }

    void src_targets_process_format_text_json(src_targets_obj * obj) {

        int ptr;

        unsigned int iTarget;
        unsigned int nTargets;

        int token_root_O;
        int token_targets_V;
        int token_targets_A;
        int token_target_V;
        int token_target_O;
        int token_tag_V;
        int token_tag_S;
        int token_x_V;
        int token_x_N;
        int token_y_V;
        int token_y_N;
        int token_z_V;
        int token_z_N;

        json_tokens_clear(obj->tokens);
        ptr = json_tokens_parse(obj->tokens, obj->string);

        if (ptr == -1) {
            printf("Cannot parse JSON string.");
            exit(EXIT_FAILURE);
        }

        token_root_O = json_tokens_getFromValue(obj->tokens, obj->string, -1);
        if (token_root_O == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }       

        token_targets_V = json_tokens_getFromObject(obj->tokens, obj->string, token_root_O, "targets");
        if (token_targets_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        token_targets_A = json_tokens_getFromValue(obj->tokens, obj->string, token_targets_V);
        if (token_targets_A == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        nTargets = json_tokens_count(obj->tokens, obj->string, token_targets_A);

        for (iTarget = 0; iTarget < nTargets; iTarget++) {

            token_target_V = json_tokens_getFromArray(obj->tokens, obj->string, token_targets_A, iTarget);
            if (token_target_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_target_O = json_tokens_getFromValue(obj->tokens, obj->string, token_target_V);
            if (token_target_O == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_tag_V = json_tokens_getFromObject(obj->tokens, obj->string, token_target_O, "tag");
            if (token_tag_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_tag_S = json_tokens_getFromValue(obj->tokens, obj->string, token_tag_V);
            if (token_tag_S == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_x_V = json_tokens_getFromObject(obj->tokens, obj->string, token_target_O, "x");
            if (token_x_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_x_N = json_tokens_getFromValue(obj->tokens, obj->string, token_x_V);
            if (token_x_N == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }
            
            token_y_V = json_tokens_getFromObject(obj->tokens, obj->string, token_target_O, "y");
            if (token_y_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_y_N = json_tokens_getFromValue(obj->tokens, obj->string, token_y_V);
            if (token_y_N == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_z_V = json_tokens_getFromObject(obj->tokens, obj->string, token_target_O, "z");
            if (token_z_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_z_N = json_tokens_getFromValue(obj->tokens, obj->string, token_z_V);
            if (token_z_N == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            json_tokens_extractString(obj->tokens, obj->string, token_tag_S, obj->out->targets->tags[iTarget]);
            json_tokens_extractFloat(obj->tokens, obj->string, token_x_N, &(obj->out->targets->array[iTarget * 3 + 0]));
            json_tokens_extractFloat(obj->tokens, obj->string, token_y_N, &(obj->out->targets->array[iTarget * 3 + 1]));
            json_tokens_extractFloat(obj->tokens, obj->string, token_z_N, &(obj->out->targets->array[iTarget * 3 + 2]));

        }

        obj->timeStamp++;

        obj->out->timeStamp = obj->timeStamp;
        obj->out->fS = obj->fS;

    }

    src_targets_cfg * src_targets_cfg_construct(void) {

        src_targets_cfg * cfg;

        cfg = (src_targets_cfg *) malloc(sizeof(src_targets_cfg));

        return cfg;

    }

    void src_targets_cfg_destroy(src_targets_cfg * cfg) {

        if (cfg->format != NULL) {
            format_destroy(cfg->format);
        }

        if (cfg->interface != NULL) {
            interface_destroy(cfg->interface);
        }

        if (cfg->targets != NULL) {
            targets_destroy(cfg->targets);
        }

        free((void *) cfg);        

    }

    void src_targets_cfg_printf(const src_targets_cfg * cfg) {

        // To be done

    }