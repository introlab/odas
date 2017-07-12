    
    #include "src_hops.h"

    src_hops_obj * src_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config) {

        src_hops_obj * obj;
        unsigned int nBytes;

        obj = (src_hops_obj *) malloc(sizeof(src_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        obj->fS = src_hops_config->fS;
        
        obj->format = format_clone(src_hops_config->format);
        obj->interface = interface_clone(src_hops_config->interface);

        memset(obj->bytes, 0x00, 4 * sizeof(char));

        switch (obj->format->type) {
            
            case format_bin08: nBytes = 1; break;
            case format_bin16: nBytes = 2; break;
            case format_bin24: nBytes = 3; break;
            case format_bin32: nBytes = 4; break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }       

        obj->buffer = (char *) malloc(sizeof(char) * obj->hopSize * obj->nChannels * nBytes);

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

            case interface_file:

                src_hops_open_file(obj);

            break;

            case interface_socket:

                src_hops_open_socket(obj);

            break;

            case interface_soundcard:

                src_hops_open_soundcard(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }        

    }

    void src_hops_open_file(src_hops_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "rb");

    }

    void src_hops_open_socket(src_hops_obj * obj) {

        printf("Not implemented yet.\n");
        exit(EXIT_FAILURE);

    }

    void src_hops_open_soundcard(src_hops_obj * obj) {

        snd_pcm_hw_params_t * hw_params;
        snd_pcm_format_t format;
        int err;
        char * tmpStr;

        switch (obj->format->type) {
            
            case format_bin08:

                format = SND_PCM_FORMAT_S8;

            break;

            case format_bin16:

                format = SND_PCM_FORMAT_S16_LE;

            break;

            case format_bin24:

                format = SND_PCM_FORMAT_S24_LE;

            break;
            
            case format_bin32:
            
                format = SND_PCM_FORMAT_S32_LE;
            
            break;

            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }       

        tmpStr = (char *) malloc(sizeof(char) * 1024);
        sprintf(tmpStr, "hw:%u,%u", obj->interface->card, obj->interface->device);

        if ((err = snd_pcm_open(&(obj->ch), tmpStr, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
            printf("Cannot open audio device %s: %s\n",tmpStr, snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        free((void *) tmpStr);

        if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
            printf("Cannot allocate hardware parameter structure: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_any(obj->ch, hw_params)) < 0) {
            printf("Cannot initialize hardware parameter structure: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_access(obj->ch, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
            printf("Cannot set access type: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_format(obj->ch, hw_params, format)) < 0) {
            printf("Cannot set sample format: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_rate(obj->ch, hw_params, obj->fS, 0)) < 0) {
            printf("Cannot set sample rate: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_channels(obj->ch, hw_params, obj->nChannels)) < 0) {
            printf("Cannot set channel count: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params(obj->ch, hw_params)) < 0) {
            printf("Cannot set parameters: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        snd_pcm_hw_params_free(hw_params);

        if ((err = snd_pcm_prepare(obj->ch)) < 0) {
            printf("Cannot prepare audio interface for use: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

    }

    void src_hops_close(src_hops_obj * obj) {

        switch(obj->interface->type) {

            case interface_file:

                src_hops_close_file(obj);

            break;

            case interface_socket:

                src_hops_close_socket(obj);

            break;

            case interface_soundcard:

                src_hops_close_soundcard(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void src_hops_close_file(src_hops_obj * obj) {

        fclose(obj->fp);

    }

    void src_hops_close_socket(src_hops_obj * obj) {

        printf("Not implemented yet.\n");
        exit(EXIT_FAILURE);

    }

    void src_hops_close_soundcard(src_hops_obj * obj) {

        snd_pcm_close(obj->ch);

    }

    int src_hops_process(src_hops_obj * obj) {

        int rtnValue;

        switch(obj->interface->type) {

            case interface_file:

                rtnValue = src_hops_process_file(obj);

            break;

            case interface_socket:

                rtnValue = src_hops_process_socket(obj);

            break;

            case interface_soundcard:

                rtnValue = src_hops_process_soundcard(obj);

            break;

            default:

                printf("Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

        obj->timeStamp++;
        obj->out->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    int src_hops_process_file(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;
        signed char sampleChar;
        signed short sampleShort;
        signed int sampleInt;
        float sample;
        int rtnValue;
        int nBytes;
        int nSamples;

        switch (obj->format->type) {

            case format_bin08: nBytes = 1; break;
            case format_bin16: nBytes = 2; break;
            case format_bin24: nBytes = 3; break;
            case format_bin32: nBytes = 4; break;

        }

        memset(obj->buffer, 0x00, sizeof(char) * nBytes * obj->hopSize * obj->nChannels);
        nSamples = fread(obj->buffer, sizeof(char) * nBytes, obj->hopSize * obj->nChannels, obj->fp);

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                memcpy(&(obj->bytes[4-nBytes]),
                       &(obj->buffer[(iSample * obj->nChannels + iChannel) * nBytes]),
                       sizeof(char) * nBytes);

                sample = pcm_signedXXbits2normalized(obj->bytes, nBytes);

                obj->out->hops->array[iChannel][iSample] = sample;

            }

        }

        if (nSamples != (obj->nChannels * obj->hopSize)) {
            
            rtnValue = -1;    

        }
        else {

            rtnValue = 0;

        }

        return rtnValue;

    }

    int src_hops_process_socket(src_hops_obj * obj) {

        printf("Not implemented\n");
        exit(EXIT_FAILURE);

    }

    int src_hops_process_soundcard(src_hops_obj * obj) {

        unsigned int iSample;
        unsigned int iChannel;

        int err;
        unsigned int nBytes;
        float sample;

        int rtnValue;

        switch (obj->format->type) {

            case format_bin08: nBytes = 1; break;
            case format_bin16: nBytes = 2; break;
            case format_bin24: nBytes = 3; break;
            case format_bin32: nBytes = 4; break;

        }

        if (err = snd_pcm_readi(obj->ch, obj->buffer, obj->hopSize) > 0) {

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    memcpy(&(obj->bytes[4-nBytes]),
                           &(obj->buffer[(iSample * obj->nChannels + iChannel) * nBytes]),
                           sizeof(char) * nBytes);

                    sample = pcm_signedXXbits2normalized(obj->bytes, nBytes);

                    obj->out->hops->array[iChannel][iSample] = sample;

                }

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    src_hops_cfg * src_hops_cfg_construct(void) {

        src_hops_cfg * cfg;

        cfg = (src_hops_cfg *) malloc(sizeof(src_hops_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void src_hops_cfg_destroy(src_hops_cfg * src_hops_config) {

        if (src_hops_config->format != NULL) {
            format_destroy(src_hops_config->format);
        }
        if (src_hops_config->interface != NULL) {
            interface_destroy(src_hops_config->interface);
        }

        free((void *) src_hops_config);

    }
