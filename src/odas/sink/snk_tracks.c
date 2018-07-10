   
    /**
    * \file     snk_tracks.c
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
    
    #include <sink/snk_tracks.h>

    snk_tracks_obj * snk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config) {

        snk_tracks_obj * obj;

        obj = (snk_tracks_obj *) malloc(sizeof(snk_tracks_obj));

        obj->timeStamp = 0;

        obj->nTracks = msg_tracks_config->nTracks;
        
        obj->server_id = 0;
        obj->connection_id = 0;                
        obj->port = snk_tracks_config->port;

        obj->bufferSize = 4096;
        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);

        obj->in = (msg_tracks_obj *) NULL;

        return obj;

    }

    void snk_tracks_destroy(snk_tracks_obj * obj) {

        free((void *) obj->buffer);
        free((void *) obj);

    }

    void snk_tracks_connect(snk_tracks_obj * obj, msg_tracks_obj * in) {

        obj->in = in;

    }

    void snk_tracks_disconnect(snk_tracks_obj * obj) {

        obj->in = (msg_tracks_obj *) NULL;

    }

    void snk_tracks_open(snk_tracks_obj * obj) {

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

    void snk_tracks_close(snk_tracks_obj * obj) {

        if (obj->port != 0) {

            close(obj->connection_id);
            close(obj->server_id);

            obj->server_id = 0;
            obj->connection_id = 0;

        }

    }

    int snk_tracks_process(snk_tracks_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            snk_tracks_process_format(obj);
            snk_tracks_process_interface(obj);

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_tracks_process_interface(snk_tracks_obj * obj) {

        if (obj->port != 0) {

            if (send(obj->connection_id, obj->buffer, strlen(obj->buffer), 0) < 0) {
                printf("Sink tracks: Could not send message.\n");
                exit(EXIT_FAILURE);
            }  

        }

    }

    void snk_tracks_process_format(snk_tracks_obj * obj) {

        unsigned int iTrack;

        obj->buffer[0] = 0x00;

        sprintf(&(obj->buffer[strlen(obj->buffer)]),"{\n");
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    \"timeStamp\": %llu,\n",obj->in->timeStamp);
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    \"src\": [\n");

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            sprintf(&(obj->buffer[strlen(obj->buffer)]), "        { \"id\": %llu, \"tag\": \"%s\", \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f, \"activity\": %1.3f }", 
                    obj->in->tracks->ids[iTrack],
                    obj->in->tracks->tags[iTrack],
                    obj->in->tracks->array[iTrack*3+0], 
                    obj->in->tracks->array[iTrack*3+1], 
                    obj->in->tracks->array[iTrack*3+2],
                    obj->in->tracks->activity[iTrack]);

            if (iTrack != (obj->nTracks - 1)) {

                sprintf(&(obj->buffer[strlen(obj->buffer)]),",");

            }

            sprintf(&(obj->buffer[strlen(obj->buffer)]),"\n");

        }
        
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"    ]\n");
        sprintf(&(obj->buffer[strlen(obj->buffer)]),"}\n");

    }

    snk_tracks_cfg * snk_tracks_cfg_construct(void) {

        snk_tracks_cfg * cfg;

        cfg = (snk_tracks_cfg *) malloc(sizeof(snk_tracks_cfg));

        cfg->port = 0;

        return cfg;

    }

    void snk_tracks_cfg_destroy(snk_tracks_cfg * snk_tracks_config) {

        free((void *) snk_tracks_config);

    }
