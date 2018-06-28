   
   /**
    * \file     src_hops.c
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
    
    #include <source/src_hops.h>

    src_hops_obj * src_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config) {

        src_hops_obj * obj;

        obj = (src_hops_obj *) malloc(sizeof(src_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        
        obj->server_id = 0;
        obj->connection_id = 0;
        obj->port = src_hops_config->port;        

        obj->nBytes = 2;
        obj->nSamples = obj->hopSize * obj->nChannels;
        obj->bufferSize = obj->nSamples * obj->nBytes;

        obj->bufferInterleave = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->bufferInterleave, 0x00, sizeof(char) * obj->bufferSize);
        obj->bufferPerChannel = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->bufferPerChannel, 0x00, sizeof(char) * obj->bufferSize);       
        obj->buffer = (float *) malloc(sizeof(float) * obj->nSamples);
        memset(obj->buffer, 0x00, sizeof(float) * obj->nSamples);

        obj->out = (msg_hops_obj *) NULL;
        
        return obj;

    }

    void src_hops_destroy(src_hops_obj * obj) {

        free((void *) obj->bufferInterleave);
        free((void *) obj->bufferPerChannel);
        free((void *) obj->buffer);
        free((void *) obj);

    }

    void src_hops_connect(src_hops_obj * obj, msg_hops_obj * out) {

        obj->out = out;

    }

    void src_hops_disconnect(src_hops_obj * obj) {

        obj->out = (msg_hops_obj *) NULL;

    }

    void src_hops_open(src_hops_obj * obj) {

        struct sockaddr_in server_address;

        memset(&server_address, 0x00, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(obj->port);

        obj->server_id = socket(AF_INET, SOCK_STREAM, 0);
        
        bind(obj->server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        listen(obj->server_id, 1);
        obj->connection_id = accept(obj->server_id, (struct sockaddr*) NULL, NULL); 

    }

    void src_hops_close(src_hops_obj * obj) {

        close(obj->connection_id);
        close(obj->server_id);

        obj->server_id = 0;
        obj->connection_id = 0;

    }

    int src_hops_process(src_hops_obj * obj) {

        int rtnValue;

        rtnValue = src_hops_process_interface(obj);
        src_hops_process_format(obj);

        obj->timeStamp++;
        obj->out->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    int src_hops_process_interface(src_hops_obj * obj) {

        int rtnValue;
        unsigned int nBytes;
        unsigned int messageSize;

        nBytes = 0;

        while( (messageSize = recv(obj->connection_id, &(obj->bufferInterleave[nBytes]), (obj->bufferSize-nBytes), 0)) > 0) {

            nBytes += messageSize;

            if (nBytes == obj->bufferSize) {
                break;
            }

        }

        if (messageSize == 0) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    void src_hops_process_format(src_hops_obj * obj) {

        unsigned int iChannel;

        interleave_interleave2perchannel(obj->bufferPerChannel, obj->bufferInterleave, obj->nBytes, obj->nChannels, obj->hopSize);
        pcm_SXle2normalized(obj->buffer, obj->bufferPerChannel, obj->nBytes, obj->nSamples);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            memcpy(obj->out->hops->array[iChannel], &(obj->buffer[iChannel * obj->hopSize]), obj->hopSize * sizeof(float));
        }

    }

    src_hops_cfg * src_hops_cfg_construct(void) {

        src_hops_cfg * cfg;

        cfg = (src_hops_cfg *) malloc(sizeof(src_hops_cfg));

        cfg->port = 0;

        return cfg;

    }

    void src_hops_cfg_destroy(src_hops_cfg * cfg) {

        free((void *) cfg);

    }

    void src_hops_cfg_printf(const src_hops_cfg * cfg) {

    }
