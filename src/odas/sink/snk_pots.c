   
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
        
        obj->server_id = 0;
        obj->connection_id = 0;        
        obj->port = snk_pots_config->port;

        obj->bufferSize = 4096;
        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);
        
        obj->in = (msg_pots_obj *) NULL;

        return obj;

    }

    void snk_pots_destroy(snk_pots_obj * obj) {

        free((void *) obj->buffer);
        free((void *) obj);

    }

    void snk_pots_connect(snk_pots_obj * obj, msg_pots_obj * in) {

        obj->in = in;

    }

    void snk_pots_disconnect(snk_pots_obj * obj) {

        obj->in = (msg_pots_obj *) NULL;

    }

    void snk_pots_open(snk_pots_obj * obj) {

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


    void snk_pots_close(snk_pots_obj * obj) {

        if (obj->port != 0) {

            close(obj->connection_id);
            close(obj->server_id);

            obj->server_id = 0;
            obj->connection_id = 0;

        }

    }

    int snk_pots_process(snk_pots_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            snk_pots_process_format(obj);
            snk_pots_process_interface(obj);

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_pots_process_interface(snk_pots_obj * obj) {

        if (obj->port != 0) {

            if (send(obj->connection_id, obj->buffer, strlen(obj->buffer), 0) < 0) {
                printf("Sink pots: Could not send message.\n");
                exit(EXIT_FAILURE);
            }        

        }

    }

    void snk_pots_process_format(snk_pots_obj * obj) {

        unsigned int iPot;

        obj->buffer[0] = 0x00;

        sprintf(&(obj->buffer[strlen(obj->buffer)]),"{\n");
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    \"timeStamp\": %llu,\n",obj->in->timeStamp);
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    \"src\": [\n");

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            sprintf(&(obj->buffer[strlen(obj->buffer)]),"        { \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f, \"E\": %1.3f }", 
                    obj->in->pots->array[iPot*4+0], obj->in->pots->array[iPot*4+1], obj->in->pots->array[iPot*4+2], obj->in->pots->array[iPot*4+3]);

            if (iPot != (obj->nPots - 1)) {

                sprintf(&(obj->buffer[strlen(obj->buffer)]),",");

            }

            sprintf(&(obj->buffer[strlen(obj->buffer)]),"\n");

        }
        
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    ]\n");
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"}\n");

    }

    snk_pots_cfg * snk_pots_cfg_construct(void) {

        snk_pots_cfg * cfg;

        cfg = (snk_pots_cfg *) malloc(sizeof(snk_pots_cfg));

        cfg->port = 0;

        return cfg;

    }

    void snk_pots_cfg_destroy(snk_pots_cfg * snk_pots_config) {

        free((void *) snk_pots_config);

    }
