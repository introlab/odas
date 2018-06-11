    
   /**
    * \file     dsr_targets.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-06
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

	#include <deserializer/dsr_targets.h>

    dsr_targets_obj * dsr_targets_construct(const dsr_targets_cfg * dsr_targets_config, const msg_targets_cfg * msg_targets_config) {

    	dsr_targets_obj * obj;

    	obj = (dsr_targets_obj *) malloc(sizeof(dsr_targets_obj));

        obj->timeStamp = 0;

        obj->nTargets = msg_targets_config->nTargets;
        obj->fS = msg_targets_config->fS;

        obj->tokens = json_tokens_construct(1024);
        obj->string = (char *) malloc(sizeof(char) * 256);
        memset(obj->string, 0x00, sizeof(char) * 256);

        obj->in = (char *) NULL;
        obj->out = (msg_targets_obj *) NULL;

    	return obj;

    }

    void dsr_targets_destroy(dsr_targets_obj * obj) {

    	json_tokens_destroy(obj->tokens);
    	free((void *) obj);

    }

    void dsr_targets_connect(dsr_targets_obj * obj, char * in, msg_targets_obj * out) {

    	obj->in = in;
    	obj->out = out;

    }

    void dsr_targets_disconnect(dsr_targets_obj * obj) {

    	obj->in = (char *) NULL;
    	obj->out = (msg_targets_obj *) NULL;

    }

    void dsr_targets_process(dsr_targets_obj * obj) {

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
        json_tokens_parse(obj->tokens, obj->in);

        token_root_O = json_tokens_getFromValue(obj->tokens, obj->in, -1);
        if (token_root_O == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        token_targets_V = json_tokens_getFromObject(obj->tokens, obj->in, token_root_O, "targets");
        if (token_targets_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        token_targets_A = json_tokens_getFromValue(obj->tokens, obj->in, token_targets_V);
        if (token_targets_A == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        nTargets = json_tokens_count(obj->tokens, obj->in, token_targets_A);
        if (nTargets != obj->nTargets) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        for (iTarget = 0; iTarget < nTargets; iTarget++) {

            token_target_V = json_tokens_getFromArray(obj->tokens, obj->in, token_targets_A, iTarget);
            if (token_target_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_target_O = json_tokens_getFromValue(obj->tokens, obj->in, token_target_V);
            if (token_target_O == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_tag_V = json_tokens_getFromObject(obj->tokens, obj->in, token_target_O, "tag");
            if (token_tag_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_tag_S = json_tokens_getFromValue(obj->tokens, obj->in, token_tag_V);
            if (token_tag_S == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_x_V = json_tokens_getFromObject(obj->tokens, obj->in, token_target_O, "x");
            if (token_x_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_x_N = json_tokens_getFromValue(obj->tokens, obj->in, token_x_V);
            if (token_x_N == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }
            
            token_y_V = json_tokens_getFromObject(obj->tokens, obj->in, token_target_O, "y");
            if (token_y_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_y_N = json_tokens_getFromValue(obj->tokens, obj->in, token_y_V);
            if (token_y_N == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_z_V = json_tokens_getFromObject(obj->tokens, obj->in, token_target_O, "z");
            if (token_z_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_z_N = json_tokens_getFromValue(obj->tokens, obj->in, token_z_V);
            if (token_z_N == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            json_tokens_extractString(obj->tokens, obj->in, token_tag_S, obj->out->targets->tags[iTarget]);
            json_tokens_extractFloat(obj->tokens, obj->in, token_x_N, &(obj->out->targets->array[iTarget * 3 + 0]));
            json_tokens_extractFloat(obj->tokens, obj->in, token_y_N, &(obj->out->targets->array[iTarget * 3 + 1]));
            json_tokens_extractFloat(obj->tokens, obj->in, token_z_N, &(obj->out->targets->array[iTarget * 3 + 2]));

        }

        obj->timeStamp++;

        obj->out->timeStamp = obj->timeStamp;
        obj->out->fS = obj->fS;

    }

    dsr_targets_cfg * dsr_targets_cfg_construct(void) {

    }

    void dsr_targets_cfg_destroy(dsr_targets_cfg * cfg) {

    }
