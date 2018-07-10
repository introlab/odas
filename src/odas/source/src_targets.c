   
    /**
    * \file     src_targets.c
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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
        
        obj->server_id = 0;
        obj->connection_id = 0;        
        obj->port = src_targets_config->port;

        obj->bufferSize = 4096;

        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);
        obj->string = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->string, 0x00, sizeof(char) * obj->bufferSize);

        obj->tokens = json_tokens_construct(1024);

        obj->sharedTargets = share_construct((void *) targets_construct_zero(msg_targets_config->nTargets));

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_targets_obj *) NULL;
        
        return obj;

    }

    void src_targets_destroy(src_targets_obj * obj) {

        targets_destroy((targets_obj *) share_get(obj->sharedTargets));
        share_destroy(obj->sharedTargets);
        json_tokens_destroy(obj->tokens);
        free((void *) obj->buffer);
        free((void *) obj->string);

        free((void *) obj);        

    }

    void src_targets_connect(src_targets_obj * obj, msg_hops_obj * in, msg_targets_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void src_targets_disconnect(src_targets_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_targets_obj *) NULL;

    }

    void src_targets_open(src_targets_obj * obj) {

        struct sockaddr_in server_address;

        memset(&server_address, 0x00, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(obj->port);

        obj->server_id = socket(AF_INET, SOCK_STREAM, 0);

        bind(obj->server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        listen(obj->server_id, 1);
        obj->connection_id = accept(obj->server_id, (struct sockaddr *) NULL, NULL);

    }

    void src_targets_close(src_targets_obj * obj) {

        close(obj->connection_id);
        close(obj->server_id);

        obj->server_id = 0;
        obj->connection_id = 0;

    }

    
    int src_targets_receive(src_targets_obj * obj) {

        int rtnValue;

        rtnValue = src_targets_receive_interface(obj);
        src_targets_receive_format(obj);

        return rtnValue;

    }

    int src_targets_receive_interface(src_targets_obj * obj) {
        
        int rtnValue;
        unsigned int nBytes;
        unsigned int messageSize;
        int ptr;

        nBytes = strlen(obj->buffer);

        while ((messageSize = recv(obj->connection_id, &(obj->buffer[nBytes]), (obj->bufferSize-nBytes), 0)) > 0) {

            if (messageSize == 0) {
                ptr = -1;
                break;
            }

            nBytes += messageSize;

            json_tokens_clear(obj->tokens);
            ptr = json_tokens_parse(obj->tokens, obj->buffer);

            if (ptr != -1) {

                memcpy(obj->string, obj->buffer, ptr);
                memmove(obj->buffer, &(obj->buffer[ptr]), nBytes - ptr);
                obj->buffer[nBytes - ptr] = 0x00;

                break;

            }

        }

        if (ptr != -1) {
            rtnValue = 0;
        }
        else {
            rtnValue = -1;
        }            

        return rtnValue;

    }

    void src_targets_receive_format(src_targets_obj * obj) {

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

        targets_obj * targets;

        if (strlen(obj->string) != 0) {

            targets = (targets_obj *) share_get(obj->sharedTargets);

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

                json_tokens_extractString(obj->tokens, obj->string, token_tag_S, targets->tags[iTarget]);
                json_tokens_extractFloat(obj->tokens, obj->string, token_x_N, &(targets->array[iTarget * 3 + 0]));
                json_tokens_extractFloat(obj->tokens, obj->string, token_y_N, &(targets->array[iTarget * 3 + 1]));
                json_tokens_extractFloat(obj->tokens, obj->string, token_z_N, &(targets->array[iTarget * 3 + 2]));

            }

            share_release(obj->sharedTargets, (void *) targets);

        }

    }

    int src_targets_process(src_targets_obj * obj) {

        int rtnValue;

        targets_obj * targets;

        if (msg_hops_isZero(obj->in) == 0) {

            targets = (targets_obj *) share_get(obj->sharedTargets);
            targets_copy(obj->out->targets, targets);
            share_release(obj->sharedTargets, (void *) targets);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_targets_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    } 

    src_targets_cfg * src_targets_cfg_construct(void) {

        src_targets_cfg * cfg;

        cfg = (src_targets_cfg *) malloc(sizeof(src_targets_cfg));

        cfg->port = 0;

        return cfg;

    }

    void src_targets_cfg_destroy(src_targets_cfg * cfg) {

        free((void *) cfg);        

    }

    void src_targets_cfg_printf(const src_targets_cfg * cfg) {

        // To be done

    }