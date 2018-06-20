   
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
        obj->fS = msg_hops_config->fS;
        
        obj->format = format_clone(src_hops_config->format);
        obj->interface = interface_clone(src_hops_config->interface);

        obj->fp = (FILE *) NULL;
        obj->ch = (snd_pcm_t *) NULL;
        obj->server_id = 0;
        obj->connection_id = 0;

        memset(obj->bytes, 0x00, 4 * sizeof(char));

        if (!(((obj->interface->type == interface_blackhole)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int08)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int16)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int24)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_binary_int32)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_binary_int08)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_binary_int16)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_binary_int24)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_binary_int32)) ||             
              ((obj->interface->type == interface_soundcard)  && (obj->format->type == format_binary_int08)) ||
              ((obj->interface->type == interface_soundcard)  && (obj->format->type == format_binary_int16)) ||
              ((obj->interface->type == interface_soundcard)  && (obj->format->type == format_binary_int24)) ||
              ((obj->interface->type == interface_soundcard)  && (obj->format->type == format_binary_int32)))) {
            
            printf("Source hops: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        switch (obj->format->type) {

            case format_binary_int08: obj->bufferSize = obj->hopSize * obj->nChannels * 1; break;
            case format_binary_int16: obj->bufferSize = obj->hopSize * obj->nChannels * 2; break;
            case format_binary_int24: obj->bufferSize = obj->hopSize * obj->nChannels * 3; break;
            case format_binary_int32: obj->bufferSize = obj->hopSize * obj->nChannels * 4; break;

        }      

        obj->buffer = (char *) malloc(sizeof(char) * obj->bufferSize);
        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);

        obj->out = (msg_hops_obj *) NULL;
        
        return obj;

    }

    void src_hops_destroy(src_hops_obj * obj) {

        free((void *) obj->buffer);
        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void src_hops_connect(src_hops_obj * obj, msg_hops_obj * out) {

        obj->out = out;

    }

    void src_hops_disconnect(src_hops_obj * obj) {

        obj->out = (msg_hops_obj *) NULL;

    }

    void src_hops_open(src_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                src_hops_open_interface_blackhole(obj);

            break;

            case interface_file:

                src_hops_open_interface_file(obj);

            break;

            case interface_socket:

                src_hops_open_interface_socket(obj);

            break;

            case interface_soundcard:

                src_hops_open_interface_soundcard(obj);

            break;

            default:

                printf("Source hops: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }        

    }

    void src_hops_open_interface_blackhole(src_hops_obj * obj) {

        // Do nothing

    }


    void src_hops_open_interface_file(src_hops_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "rb");

        if (obj->fp == NULL) {
            printf("Cannot open file %s\n",obj->interface->fileName);
            exit(EXIT_FAILURE);
        }

    }

    void src_hops_open_interface_socket(src_hops_obj * obj) {

        struct sockaddr_in server_address;

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(obj->interface->port);

        obj->server_id = socket(AF_INET, SOCK_STREAM, 0);
        
        bind(obj->server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        listen(obj->server_id, 1);
        obj->connection_id = accept(obj->server_id, (struct sockaddr*) NULL, NULL);

    }

    void src_hops_open_interface_soundcard(src_hops_obj * obj) {

        snd_pcm_hw_params_t * hw_params;
        snd_pcm_format_t format;
        int err;

        switch (obj->format->type) {
            
            case format_binary_int08:

                format = SND_PCM_FORMAT_S8;

            break;

            case format_binary_int16:

                format = SND_PCM_FORMAT_S16_LE;

            break;

            case format_binary_int24:

                format = SND_PCM_FORMAT_S24_LE;

            break;
            
            case format_binary_int32:
            
                format = SND_PCM_FORMAT_S32_LE;
            
            break;

            default:

                printf("Source hops: Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }       

        if ((err = snd_pcm_open(&(obj->ch), obj->interface->deviceName, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
            printf("Source hops: Cannot open audio device %s: %s\n",obj->interface->deviceName, snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
            printf("Source hops: Cannot allocate hardware parameter structure: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_any(obj->ch, hw_params)) < 0) {
            printf("Source hops: Cannot initialize hardware parameter structure: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_access(obj->ch, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
            printf("Source hops: Cannot set access type: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_format(obj->ch, hw_params, format)) < 0) {
            printf("Source hops: Cannot set sample format: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_rate(obj->ch, hw_params, obj->fS, 0)) < 0) {
            printf("Source hops: Cannot set sample rate: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_channels(obj->ch, hw_params, obj->nChannels)) < 0) {
            printf("Source hops: Cannot set channel count: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params(obj->ch, hw_params)) < 0) {
            printf("Source hops: Cannot set parameters: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        snd_pcm_hw_params_free(hw_params);

        if ((err = snd_pcm_prepare(obj->ch)) < 0) {
            printf("Source hops: Cannot prepare audio interface for use: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

    }

    void src_hops_close(src_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                src_hops_close_interface_blackhole(obj);

            break;

            case interface_file:

                src_hops_close_interface_file(obj);

            break;

            case interface_socket:

                src_hops_close_interface_socket(obj);

            break;

            case interface_soundcard:

                src_hops_close_interface_soundcard(obj);

            break;

            default:

                printf("Source hops: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void src_hops_close_interface_blackhole(src_hops_obj * obj) {

        // Do nothing

    }

    void src_hops_close_interface_file(src_hops_obj * obj) {

        fclose(obj->fp);

    }

    void src_hops_close_interface_socket(src_hops_obj * obj) {

        close(obj->connection_id);
        close(obj->server_id);

        obj->server_id = 0;
        obj->connection_id = 0;

    }

    void src_hops_close_interface_soundcard(src_hops_obj * obj) {

        snd_pcm_close(obj->ch);

    }

    int src_hops_process(src_hops_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_blackhole:

                rtnValue = src_hops_process_interface_blackhole(obj);

            break;

            case interface_file:

                rtnValue = src_hops_process_interface_file(obj);

            break;

            case interface_socket:

                rtnValue = src_hops_process_interface_socket(obj);

            break;

            case interface_soundcard:

                rtnValue = src_hops_process_interface_soundcard(obj);

            break;

            default:

                printf("Source hops: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

        switch(obj->format->type) {

            case format_binary_int08:

                src_hops_process_format_binary_int08(obj);

            break;

            case format_binary_int16:

                src_hops_process_format_binary_int16(obj);                

            break;

            case format_binary_int24:

                src_hops_process_format_binary_int24(obj);

            break;

            case format_binary_int32:

                src_hops_process_format_binary_int32(obj);

            break;

            default:

                printf("Source hops: Invalid format type.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->timeStamp++;
        obj->out->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    int src_hops_process_interface_blackhole(src_hops_obj * obj) {

        int rtnValue;

        memset(obj->buffer, 0x00, sizeof(char) * obj->bufferSize);
        rtnValue = 0;

        return rtnValue;

    }

    int src_hops_process_interface_file(src_hops_obj * obj) {

        unsigned int nBytesTotal;
        int rtnValue;

        nBytesTotal = fread(obj->buffer, sizeof(char), obj->bufferSize, obj->fp);

        if (nBytesTotal == obj->bufferSize) {
            
            rtnValue = 0;    

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int src_hops_process_interface_soundcard(src_hops_obj * obj) {

        unsigned int nSamples;
        int rtnValue;
        int err;

        if (err = snd_pcm_readi(obj->ch, obj->buffer, obj->hopSize) > 0) {
            
            rtnValue = 0;    

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    int src_hops_process_interface_socket(src_hops_obj * obj) {

        int rtnValue;
        unsigned int nBytes;
        unsigned int messageSize;

        nBytes = 0;

        while( (messageSize = recv(obj->connection_id, &(obj->buffer[nBytes]), (obj->bufferSize-nBytes), 0)) > 0) {

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

    void src_hops_process_format_binary_int08(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        unsigned int nBytes;
        float sample;

        nBytes = 1;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                memcpy(&(obj->bytes[4-nBytes]),
                       &(obj->buffer[(iSample * obj->nChannels + iChannel) * nBytes]),
                       sizeof(char) * nBytes);

                sample = pcm_signedXXbits2normalized(obj->bytes, nBytes);

                obj->out->hops->array[iChannel][iSample] = sample;

            }

        }

    }

    void src_hops_process_format_binary_int16(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        unsigned int nBytes;
        float sample;

        nBytes = 2;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                memcpy(&(obj->bytes[4-nBytes]),
                       &(obj->buffer[(iSample * obj->nChannels + iChannel) * nBytes]),
                       sizeof(char) * nBytes);

                sample = pcm_signedXXbits2normalized(obj->bytes, nBytes);

                obj->out->hops->array[iChannel][iSample] = sample;

            }

        }

    }

    void src_hops_process_format_binary_int24(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        unsigned int nBytes;
        float sample;

        nBytes = 3;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                memcpy(&(obj->bytes[4-nBytes]),
                       &(obj->buffer[(iSample * obj->nChannels + iChannel) * nBytes]),
                       sizeof(char) * nBytes);

                sample = pcm_signedXXbits2normalized(obj->bytes, nBytes);

                obj->out->hops->array[iChannel][iSample] = sample;

            }

        }

    }

    void src_hops_process_format_binary_int32(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        unsigned int nBytes;
        float sample;

        nBytes = 4;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                memcpy(&(obj->bytes[4-nBytes]),
                       &(obj->buffer[(iSample * obj->nChannels + iChannel) * nBytes]),
                       sizeof(char) * nBytes);

                sample = pcm_signedXXbits2normalized(obj->bytes, nBytes);

                obj->out->hops->array[iChannel][iSample] = sample;

            }

        }

    }

    src_hops_cfg * src_hops_cfg_construct(void) {

        src_hops_cfg * cfg;

        cfg = (src_hops_cfg *) malloc(sizeof(src_hops_cfg));

        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_hops_cfg_destroy(src_hops_cfg * cfg) {

        if (cfg->format != NULL) {
            format_destroy(cfg->format);
        }
        if (cfg->interface != NULL) {
            interface_destroy(cfg->interface);
        }

        free((void *) cfg);

    }

    void src_hops_cfg_printf(const src_hops_cfg * cfg) {

    }
