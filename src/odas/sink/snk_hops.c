   
   /**
    * \file     snk_hops.c
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
    
    #include <sink/snk_hops.h>

    snk_hops_obj * snk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config) {

        snk_hops_obj * obj;

        obj = (snk_hops_obj *) malloc(sizeof(snk_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        
        obj->server_id = 0;
        obj->connection_id = 0;
        obj->port = snk_hops_config->port;        

        obj->nBytes = 2;
        obj->bufferSize = obj->nChannels * obj->hopSize * obj->nBytes;

        obj->bufferInterleave = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->bufferInterleave, 0x00, sizeof(char) * obj->bufferSize);
        obj->bufferPerChannel = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->bufferPerChannel, 0x00, sizeof(char) * obj->bufferSize);

        obj->in = (msg_hops_obj *) NULL;

        return obj;

    }

    void snk_hops_destroy(snk_hops_obj * obj) {

        free((void *) obj->bufferInterleave);
        free((void *) obj->bufferPerChannel);
        free((void *) obj);

    }

    void snk_hops_connect(snk_hops_obj * obj, msg_hops_obj * in) {

        obj->in = in;

    }

    void snk_hops_disconnect(snk_hops_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;

    }

    void snk_hops_open(snk_hops_obj * obj) {

        struct sockaddr_in server_address;

        if (obj->port != 0) {

            memset(&server_address, 0x00, sizeof(server_address));
            server_address.sin_family = AF_INET;
            server_address.sin_addr.s_addr = htonl(INADDR_ANY);
            server_address.sin_port = htons(obj->port);

            obj->server_id = socket(AF_INET, SOCK_STREAM, 0);

            bind(obj->server_id, (struct sockaddr *) &server_address, sizeof(server_address));
            listen(obj->server_id, 1);
            obj->connection_id = accept(obj->server_id, (struct sockaddr *) NULL, NULL);

        }

    }

    void snk_hops_close(snk_hops_obj * obj) {

        if (obj->port != 0) {

            close(obj->connection_id);
            close(obj->server_id);

            obj->server_id = 0;
            obj->connection_id = 0;

        }

    }

    int snk_hops_process(snk_hops_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            snk_hops_process_format(obj);
            snk_hops_process_interface(obj);

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_hops_process_interface(snk_hops_obj * obj) {

        if (obj->port != 0) {

            if (send(obj->connection_id, obj->bufferInterleave, obj->bufferSize, 0) < 0) {
                printf("Sink hops: Could not send message.\n");
                exit(EXIT_FAILURE);           
            }

        }

    }

    void snk_hops_process_format(snk_hops_obj * obj) {

        unsigned int iChannel;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            pcm_normalized2SXle(&(obj->bufferPerChannel[iChannel * obj->hopSize * obj->nBytes]), obj->in->hops->array[iChannel], obj->nBytes, obj->hopSize);
        }

        interleave_perchannel2interleave(obj->bufferInterleave, obj->bufferPerChannel, obj->nBytes, obj->nChannels, obj->hopSize);

    }

    snk_hops_cfg * snk_hops_cfg_construct(void) {

        snk_hops_cfg * cfg;

        cfg = (snk_hops_cfg *) malloc(sizeof(snk_hops_cfg));

        cfg->port = 0;

        return cfg;

    }

    void snk_hops_cfg_destroy(snk_hops_cfg * snk_hops_config) {

        free((void *) snk_hops_config);

    }
