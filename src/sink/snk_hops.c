   
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
        obj->fS = snk_hops_config->fS;
        
        obj->format = format_clone(snk_hops_config->format);
        obj->interface = interface_clone(snk_hops_config->interface);

        memset(obj->bytes, 0x00, 4 * sizeof(char));

        if (!(((obj->interface->type == interface_blackhole)  && (obj->format->type == format_undefined)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int08)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int16)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int24)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int32)) ||
              ((obj->interface->type == interface_socket)  && (obj->format->type == format_binary_int08)) ||
              ((obj->interface->type == interface_socket)  && (obj->format->type == format_binary_int16)) ||
              ((obj->interface->type == interface_socket)  && (obj->format->type == format_binary_int24)) ||
              ((obj->interface->type == interface_socket)  && (obj->format->type == format_binary_int32)))) {
            
            printf("Sink hops: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        obj->buffer = (char *) malloc(sizeof(char) * msg_hops_config->nChannels * msg_hops_config->hopSize * 4);
        memset(obj->buffer, 0x00, sizeof(char) * msg_hops_config->nChannels * msg_hops_config->hopSize * 4);
        obj->bufferSize = 0;

        obj->in = (msg_hops_obj *) NULL;

        return obj;

    }

    void snk_hops_destroy(snk_hops_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);
        free((void *) obj->buffer);

        free((void *) obj);

    }

    void snk_hops_connect(snk_hops_obj * obj, msg_hops_obj * in) {

        obj->in = in;

    }

    void snk_hops_disconnect(snk_hops_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;

    }

    void snk_hops_open(snk_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_hops_open_interface_blackhole(obj);

            break;

            case interface_file:

                snk_hops_open_interface_file(obj);

            break;

            case interface_socket:

                snk_hops_open_interface_socket(obj);

            break;

            default:

                printf("Sink hops: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    void snk_hops_open_interface_blackhole(snk_hops_obj * obj) {

        // Empty

    }

    void snk_hops_open_interface_file(snk_hops_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "wb");

        if (obj->fp == NULL) {
            printf("Cannot open file %s\n",obj->interface->fileName);
            exit(EXIT_FAILURE);
        }

    }

    void snk_hops_open_interface_socket(snk_hops_obj * obj) {

        memset(&(obj->sserver), 0x00, sizeof(struct sockaddr_in));

        obj->sserver.sin_family = AF_INET;
        obj->sserver.sin_addr.s_addr = inet_addr(obj->interface->ip);
        obj->sserver.sin_port = htons(obj->interface->port);
        obj->sid = socket(AF_INET, SOCK_STREAM, 0);

        if ( (connect(obj->sid, (struct sockaddr *) &(obj->sserver), sizeof(obj->sserver))) < 0 ) {

            printf("Sink hops: Cannot connect to server\n");
            exit(EXIT_FAILURE);

        }          

    }

    void snk_hops_close(snk_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_hops_close_interface_blackhole(obj);

            break;

            case interface_file:

                snk_hops_close_interface_file(obj);

            break;

            case interface_socket:

                snk_hops_close_interface_socket(obj);

            break;

            default:

                printf("Sink hops: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_hops_close_interface_blackhole(snk_hops_obj * obj) {

        // Empty

    }

    void snk_hops_close_interface_file(snk_hops_obj * obj) {

        fclose(obj->fp);

    }

    void snk_hops_close_interface_socket(snk_hops_obj * obj) {

        close(obj->sid);

    }

    int snk_hops_process(snk_hops_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_binary_int08:

                    snk_hops_process_format_binary_int08(obj);

                break;

                case format_binary_int16:

                    snk_hops_process_format_binary_int16(obj);                

                break;

                case format_binary_int24:

                    snk_hops_process_format_binary_int24(obj);

                break;

                case format_binary_int32:

                    snk_hops_process_format_binary_int32(obj);

                break;

                case format_undefined:

                    snk_hops_process_format_undefined(obj);

                break;

                default:

                    printf("Sink hops: Invalid format type.\n");
                    exit(EXIT_FAILURE);

                break;

            }

            switch(obj->interface->type) {

                case interface_blackhole:

                    snk_hops_process_interface_blackhole(obj);

                break;  

                case interface_file:

                    snk_hops_process_interface_file(obj);

                break;

                case interface_socket:

                    snk_hops_process_interface_socket(obj);

                break;

                default:

                    printf("Sink hops: Invalid interface type.\n");
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

    void snk_hops_process_interface_blackhole(snk_hops_obj * obj) {

        // Emtpy

    }

    void snk_hops_process_interface_file(snk_hops_obj * obj) {

        fwrite(obj->buffer, sizeof(char), obj->bufferSize, obj->fp);

    }

    void snk_hops_process_interface_socket(snk_hops_obj * obj) {

        if (send(obj->sid, obj->buffer, obj->bufferSize, 0) < 0) {
            printf("Sink hops: Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    void snk_hops_process_format_binary_int08(snk_hops_obj * obj) {

        unsigned int iChannel;
        unsigned int iSample;
        float sample;
        unsigned int nBytes;
        unsigned int nBytesTotal;

        nBytes = 1;
        nBytesTotal = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                sample = obj->in->hops->array[iChannel][iSample];
                pcm_normalized2signedXXbits(sample, nBytes, obj->bytes);
                memcpy(&(obj->buffer[nBytesTotal]), &(obj->bytes[4-nBytes]), sizeof(char) * nBytes);

                nBytesTotal += nBytes;

            }

        }

        obj->bufferSize = nBytesTotal;

    }

    void snk_hops_process_format_binary_int16(snk_hops_obj * obj) {

        unsigned int iChannel;
        unsigned int iSample;
        float sample;
        unsigned int nBytes;
        unsigned int nBytesTotal;

        nBytes = 2;
        nBytesTotal = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                sample = obj->in->hops->array[iChannel][iSample];
                pcm_normalized2signedXXbits(sample, nBytes, obj->bytes);
                memcpy(&(obj->buffer[nBytesTotal]), &(obj->bytes[4-nBytes]), sizeof(char) * nBytes);

                nBytesTotal += nBytes;


            }

        }

        obj->bufferSize = nBytesTotal;

    }

    void snk_hops_process_format_binary_int24(snk_hops_obj * obj) {

        unsigned int iChannel;
        unsigned int iSample;
        float sample;
        unsigned int nBytes;
        unsigned int nBytesTotal;

        nBytes = 3;
        nBytesTotal = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                sample = obj->in->hops->array[iChannel][iSample];
                pcm_normalized2signedXXbits(sample, nBytes, obj->bytes);
                memcpy(&(obj->buffer[nBytesTotal]), &(obj->bytes[4-nBytes]), sizeof(char) * nBytes);

                nBytesTotal += nBytes;

            }

        }

        obj->bufferSize = nBytesTotal;

    }    

    void snk_hops_process_format_binary_int32(snk_hops_obj * obj) {

        unsigned int iChannel;
        unsigned int iSample;
        float sample;
        unsigned int nBytes;
        unsigned int nBytesTotal;

        nBytes = 4;
        nBytesTotal = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                sample = obj->in->hops->array[iChannel][iSample];
                pcm_normalized2signedXXbits(sample, nBytes, obj->bytes);
                memcpy(&(obj->buffer[nBytesTotal]), &(obj->bytes[4-nBytes]), sizeof(char) * nBytes);

                nBytesTotal += nBytes;

            }

        }

        obj->bufferSize = nBytesTotal;

    }

    void snk_hops_process_format_undefined(snk_hops_obj * obj) {

        obj->buffer[0] = 0x00;
        obj->bufferSize = 0;

    }

    snk_hops_cfg * snk_hops_cfg_construct(void) {

        snk_hops_cfg * cfg;

        cfg = (snk_hops_cfg *) malloc(sizeof(snk_hops_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_hops_cfg_destroy(snk_hops_cfg * snk_hops_config) {

        if (snk_hops_config->format != NULL) {
            format_destroy(snk_hops_config->format);
        }
        if (snk_hops_config->interface != NULL) {
            interface_destroy(snk_hops_config->interface);
        }

        free((void *) snk_hops_config);

    }
