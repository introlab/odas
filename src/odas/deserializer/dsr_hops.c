
   /**
    * \file     dsr_hops.c
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

	#include <deserializer/dsr_hops.h>

    dsr_hops_obj * dsr_hops_construct(const dsr_hops_cfg * dsr_hops_config, const msg_hops_cfg * msg_hops_config) {

    	dsr_hops_obj * obj;

    	obj = (dsr_hops_obj *) malloc(sizeof(dsr_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        obj->fS = msg_hops_config->fS;

        obj->tokens = json_tokens_construct(65536);

        obj->samples = (char **) malloc(sizeof(char *) * obj->hopSize);
        memset(obj->samples, 0x00, sizeof(char *) * obj->hopSize);

        obj->in = (char *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    	return obj;

    }

    void dsr_hops_destroy(dsr_hops_obj * obj) {

    	json_tokens_destroy(obj->tokens);

    	free((void *) obj);

    }

    void dsr_hops_connect(dsr_hops_obj * obj, char * in, msg_hops_obj * out) {

    	obj->in = in;
    	obj->out = out;

    }

    void dsr_hops_disconnect(dsr_hops_obj * obj) {

    	obj->in = NULL;
    	obj->out = NULL;

    }

    void dsr_hops_process(dsr_hops_obj * obj) {

        unsigned int iChannel;
        unsigned int nChannels;
        unsigned int nSamples;

        int token_root_O;
        int token_hops_V;
        int token_hops_A;
        int token_hop_V;
        int token_hop_A;

        json_tokens_clear(obj->tokens);
        json_tokens_parse(obj->tokens, obj->in);

        token_root_O = json_tokens_getFromValue(obj->tokens, obj->in, -1);
        if (token_root_O == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        token_hops_V = json_tokens_getFromObject(obj->tokens, obj->in, token_root_O, "hops");
        if (token_hops_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        token_hops_A = json_tokens_getFromValue(obj->tokens, obj->in, token_hops_V);
        if (token_hops_A == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        nChannels = json_tokens_count(obj->tokens, obj->in, token_hops_A);
        if (nChannels != obj->nChannels) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

        for (iChannel = 0; iChannel < nChannels; iChannel++) {

            token_hop_V = json_tokens_getFromArray(obj->tokens, obj->in, token_hops_A, iChannel);
            if (token_hop_V == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            token_hop_A = json_tokens_getFromValue(obj->tokens, obj->in, token_hop_V);
            if (token_hop_A == -1) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            nSamples = json_tokens_count(obj->tokens, obj->in, token_hop_A);
            if (nSamples != obj->hopSize) { printf("Invalid JSON format.\n"); exit(EXIT_FAILURE); }

            json_tokens_extractFloats(obj->tokens, obj->in, token_hop_A, obj->out->hops->array[iChannel]);

        }

        obj->timeStamp++;

        obj->out->timeStamp = obj->timeStamp;
        obj->out->fS = obj->fS;

    }

    dsr_hops_cfg * dsr_hops_cfg_construct(void) {

    }

    void dsr_hops_cfg_destroy(dsr_hops_cfg * cfg) {

    }

