
    #include "parameters.h"

    int parameters_lookup_int(const char * file, const char * path) {

        config_t cfg;
        config_setting_t * setting;
        int rtnValue;

        config_init(&cfg); 

        if(!config_read_file(&cfg, file))
        {
            
            printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
          
            exit(EXIT_FAILURE);

        }       

        if ((setting = config_lookup(&cfg, path)) == NULL) {

            printf("Cannot find path \"%s\" in config file \"%s\"\n",path,file);

            exit(EXIT_FAILURE);

        }

        rtnValue = config_setting_get_int(setting);

        config_destroy(&cfg);   

        return rtnValue;

    }

    float parameters_lookup_float(const char * file, const char * path) {

        config_t cfg;
        config_setting_t * setting;
        float rtnValue;

        config_init(&cfg); 

        if(!config_read_file(&cfg, file))
        {
            
            printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
          
            exit(EXIT_FAILURE);

        }       

        if ((setting = config_lookup(&cfg, path)) == NULL) {

            printf("Cannot find path \"%s\" in config file \"%s\"\n",path,file);

            exit(EXIT_FAILURE);

        }

        rtnValue = (float) config_setting_get_float(setting);

        config_destroy(&cfg);   

        return rtnValue;

    }

    char * parameters_lookup_string(const char * file, const char * path) {

        config_t cfg;
        config_setting_t * setting;
        const char * tmpStr;
        char * rtnStr;

        config_init(&cfg); 

        if(!config_read_file(&cfg, file))
        {
            
            printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
          
            exit(EXIT_FAILURE);

        }       

        if ((setting = config_lookup(&cfg, path)) == NULL) {

            printf("Cannot find path \"%s\" in config file \"%s\"\n",path,file);

            exit(EXIT_FAILURE);

        }

        tmpStr = config_setting_get_string(setting);

        rtnStr = (char *) malloc(sizeof(char) * (strlen(tmpStr)+1));
        strcpy(rtnStr, tmpStr);

        config_destroy(&cfg);   

        return rtnStr;        

    }

    unsigned int parameters_count(const char * file, const char * path) {

        config_t cfg;
        config_setting_t * setting;
        unsigned int rtnValue;

        config_init(&cfg); 

        if(!config_read_file(&cfg, file))
        {
            
            printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
          
            exit(EXIT_FAILURE);

        }       

        if ((setting = config_lookup(&cfg, path)) == NULL) {

            printf("Cannot find path \"%s\" in config file \"%s\"\n",path,file);

            exit(EXIT_FAILURE);

        }

        rtnValue = config_setting_length(setting);

        config_destroy(&cfg);   

        return rtnValue;

    }

    src_hops_cfg * parameters_src_hops_raw_config(const char * fileConfig, const char * fileIOs) {

        src_hops_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = src_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "raw.fS");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileIOs, "input.raw.format");

            if (strcmp(tmpStr1, "bin08") == 0) { cfg->format = format_construct_bin(8); }
            else if (strcmp(tmpStr1, "bin16") == 0) { cfg->format = format_construct_bin(16); }
            else if (strcmp(tmpStr1, "bin24") == 0) { cfg->format = format_construct_bin(24); }
            else if (strcmp(tmpStr1, "bin32") == 0) { cfg->format = format_construct_bin(32); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileIOs, "input.raw.type");

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileIOs, "input.raw.path");

                cfg->interface = interface_construct_file(tmpStr2);

                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileIOs, "input.raw.ip");
                tmpInt1 = parameters_lookup_int(fileIOs, "input.raw.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);

                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "soundcard") == 0) {

                tmpInt1 = parameters_lookup_int(fileIOs, "input.raw.card");
                tmpInt2 = parameters_lookup_int(fileIOs, "input.raw.device");

                cfg->interface = interface_construct_soundcard(tmpInt1, tmpInt2);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_raw_config(const char * fileConfig, const char * fileIOs) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "raw.fS");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "raw.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_lookup_int(fileConfig, "raw.nChannels");

        return cfg;

    }

    unsigned int parameters_snk_hops_raw_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.raw");

    }

    snk_hops_cfg * parameters_snk_hops_raw_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_hops_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_hops_cfg_construct();

        // +------------------------------------------------------+
        // | Sample rate                                          |
        // +------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "raw.fS");

        // +------------------------------------------------------+
        // | Format                                               |
        // +------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.raw.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "bin08") == 0) { cfg->format = format_construct_bin(8); }
            else if (strcmp(tmpStr1, "bin16") == 0) { cfg->format = format_construct_bin(16); }
            else if (strcmp(tmpStr1, "bin24") == 0) { cfg->format = format_construct_bin(24); }
            else if (strcmp(tmpStr1, "bin32") == 0) { cfg->format = format_construct_bin(32); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +------------------------------------------------------+
        // | Type                                                 |
        // +------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.raw.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.raw.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.raw.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.raw.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "soundcard") == 0) {

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.raw.[%u].device", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.raw.[%u].subdevice", iSink);                
                tmpInt2 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_soundcard(tmpInt1, tmpInt2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }        

            free((void *) tmpStr1);

        return cfg;

    }

    mod_mapping_cfg * parameters_mod_mapping_config(const char * fileConfig, const char * fileIOs) {

        mod_mapping_cfg * cfg;
        unsigned int nLinks;
        unsigned int iLink;
        char * tmpStr1;

        cfg = mod_mapping_cfg_construct();

        // +----------------------------------------------------------+
        // | Links                                                    |
        // +----------------------------------------------------------+

            nLinks = parameters_count(fileConfig, "mapping.map");
            cfg->links = links_construct_zero(nLinks);

            for (iLink = 0; iLink < nLinks; iLink++) {
                
                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "mapping.map.[%u]", iLink);
                cfg->links->array[iLink] = parameters_lookup_int(fileConfig, tmpStr1);
                free((void *) tmpStr1);

            }

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_mapping_config(const char * fileConfig, const char * fileIOs) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "raw.fS");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "raw.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "mapping.map");

        return cfg;

    }

    unsigned int parameters_snk_hops_mapping_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.mapping");

    }

    snk_hops_cfg * parameters_snk_hops_mapping_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_hops_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_hops_cfg_construct();

        // +------------------------------------------------------+
        // | Sample rate                                          |
        // +------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "raw.fS");

        // +------------------------------------------------------+
        // | Format                                               |
        // +------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.mapping.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "bin08") == 0) { cfg->format = format_construct_bin(8); }
            else if (strcmp(tmpStr1, "bin16") == 0) { cfg->format = format_construct_bin(16); }
            else if (strcmp(tmpStr1, "bin24") == 0) { cfg->format = format_construct_bin(24); }
            else if (strcmp(tmpStr1, "bin32") == 0) { cfg->format = format_construct_bin(32); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +------------------------------------------------------+
        // | Type                                                 |
        // +------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.mapping.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.mapping.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.mapping.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.mapping.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "soundcard") == 0) {

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.mapping.[%u].device", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.mapping.[%u].subdevice", iSink);                
                tmpInt2 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_soundcard(tmpInt1, tmpInt2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }        

            free((void *) tmpStr1);

        return cfg;

    }

    mod_resample_cfg * parameters_mod_resample_config(const char * fileConfig, const char * fileIOs) {

        mod_resample_cfg * cfg;

        cfg = mod_resample_cfg_construct();

        unsigned int fSin;
        unsigned int fSout;

        // +----------------------------------------------------------+
        // | Sample rates                                             |
        // +----------------------------------------------------------+

            cfg->fSin = parameters_lookup_int(fileConfig, "raw.fS");        
            cfg->fSout = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_resample_config(const char * fileConfig, const char * fileIOs) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "general.size.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "mapping.map");

        return cfg;

    }

    unsigned int parameters_snk_hops_resample_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.resample");

    }

    snk_hops_cfg * parameters_snk_hops_resample_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_hops_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_hops_cfg_construct();

        // +------------------------------------------------------+
        // | Sample rate                                          |
        // +------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +------------------------------------------------------+
        // | Format                                               |
        // +------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.resample.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "bin08") == 0) { cfg->format = format_construct_bin(8); }
            else if (strcmp(tmpStr1, "bin16") == 0) { cfg->format = format_construct_bin(16); }
            else if (strcmp(tmpStr1, "bin24") == 0) { cfg->format = format_construct_bin(24); }
            else if (strcmp(tmpStr1, "bin32") == 0) { cfg->format = format_construct_bin(32); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +------------------------------------------------------+
        // | Type                                                 |
        // +------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.resample.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.resample.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.resample.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.resample.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "soundcard") == 0) {

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.resample.[%u].device", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.resample.[%u].subdevice", iSink);                
                tmpInt2 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_soundcard(tmpInt1, tmpInt2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }        

            free((void *) tmpStr1);

        return cfg;

    }

    mod_stft_cfg * parameters_mod_stft_config(const char * fileConfig, const char * fileIOs) {

        mod_stft_cfg * cfg;

        cfg = mod_stft_cfg_construct();

        return cfg;

    }

    msg_spectra_cfg * parameters_msg_spectra_stft_config(const char * fileConfig, const char * fileIOs) {

        msg_spectra_cfg * cfg;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        cfg = msg_spectra_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->halfFrameSize = parameters_lookup_int(fileConfig, "general.size.frameSize") / 2 + 1;

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "mapping.map");

        return cfg;

    }

    unsigned int parameters_snk_spectra_stft_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.stft");

    }

    snk_spectra_cfg * parameters_snk_spectra_stft_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_spectra_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_spectra_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.stft.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "float") == 0) { cfg->format = format_construct_float(); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.stft.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.stft.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.stft.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.stft.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    mod_ssl_cfg * parameters_mod_ssl_config(const char * fileConfig, const char * fileIOs) {

        mod_ssl_cfg * cfg;

        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int iSample;
        unsigned int iLevel;

        char * tmpLabel;

        cfg = mod_ssl_cfg_construct();

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            nChannels = parameters_count(fileConfig, "general.mics");

            cfg->mics = mics_construct_zero(nChannels);

            for (iChannel = 0; iChannel < nChannels; iChannel++) {

                // +--------------------------------------------------+
                // | Mu                                               |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 3; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].mu.[%u]", iChannel, iSample);
                        cfg->mics->mu[iChannel * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    }

                // +--------------------------------------------------+
                // | Sigma2                                           |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 9; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].sigma2.[%u]", iChannel, iSample);
                        cfg->mics->sigma2[iChannel * 9 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    }            

                // +--------------------------------------------------+
                // | Direction                                        |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 3; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].direction.[%u]", iChannel, iSample);
                        cfg->mics->direction[iChannel * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    } 

                // +--------------------------------------------------+
                // | Angle                                            |
                // +--------------------------------------------------+

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.mics.[%u].angle.[%u]", iChannel, 0);
                    cfg->mics->thetaAllPass[iChannel] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.mics.[%u].angle.[%u]", iChannel, 1);
                    cfg->mics->thetaNoPass[iChannel] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

            }

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->samplerate = samplerate_construct_zero();

            cfg->samplerate->mu = parameters_lookup_int(fileConfig, "general.samplerate.mu");
            cfg->samplerate->sigma2 = parameters_lookup_float(fileConfig, "general.samplerate.sigma2");

        // +----------------------------------------------------------+
        // | Sound speed                                              |
        // +----------------------------------------------------------+

            cfg->soundspeed = soundspeed_construct_zero();

            cfg->soundspeed->mu = parameters_lookup_float(fileConfig, "general.speedofsound.mu");
            cfg->soundspeed->sigma2 = parameters_lookup_float(fileConfig, "general.speedofsound.sigma2");

        // +----------------------------------------------------------+
        // | Epsilon                                                  |
        // +----------------------------------------------------------+

            cfg->epsilon = parameters_lookup_float(fileConfig, "general.epsilon");

        // +----------------------------------------------------------+
        // | Levels                                                   |
        // +----------------------------------------------------------+
            
            cfg->nLevels = parameters_count(fileConfig, "ssl.scans");

            cfg->levels = (unsigned int *) malloc(sizeof(unsigned int) * cfg->nLevels);
            cfg->deltas = (signed int *) malloc(sizeof(signed int) * cfg->nLevels);

            for (iLevel = 0; iLevel < cfg->nLevels; iLevel++) {

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "ssl.scans.[%u].level", iLevel);
                cfg->levels[iLevel] = parameters_lookup_int(fileConfig, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "ssl.scans.[%u].delta", iLevel);
                cfg->deltas[iLevel] = parameters_lookup_int(fileConfig, tmpLabel);
                free((void *) tmpLabel);

            }

        // +----------------------------------------------------------+
        // | Matches                                                  |
        // +----------------------------------------------------------+

            cfg->nMatches = parameters_lookup_int(fileConfig, "ssl.nMatches");

        // +----------------------------------------------------------+
        // | Minimum probability                                      |
        // +----------------------------------------------------------+

            cfg->probMin = parameters_lookup_float(fileConfig, "ssl.probMin");

        // +----------------------------------------------------------+
        // | Number of refined levels                                 |
        // +----------------------------------------------------------+

            cfg->nRefinedLevels = parameters_lookup_int(fileConfig, "ssl.nRefinedLevels");

        // +----------------------------------------------------------+
        // | Number of thetas                                         |
        // +----------------------------------------------------------+

            cfg->nThetas = parameters_lookup_int(fileConfig, "ssl.nThetas");

        // +----------------------------------------------------------+
        // | Number of thetas                                         |
        // +----------------------------------------------------------+

            cfg->gainMin = parameters_lookup_float(fileConfig, "ssl.gainMin");

        return cfg;

    }

    msg_pots_cfg * parameters_msg_pots_ssl_config(const char * fileConfig, const char * fileIOs) {

        msg_pots_cfg * cfg;

        cfg = msg_pots_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        // +----------------------------------------------------------+
        // | Number of potential sources                              |
        // +----------------------------------------------------------+

            cfg->nPots = parameters_lookup_int(fileConfig, "ssl.nPots");

        return cfg;

    }

    unsigned int parameters_snk_pots_ssl_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.ssl");

    }

    snk_pots_cfg * parameters_snk_pots_ssl_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_pots_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_pots_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.ssl.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "float") == 0) { cfg->format = format_construct_float(); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.ssl.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.ssl.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.ssl.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.ssl.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    mod_sst_cfg * parameters_mod_sst_config(const char * fileConfig, const char * fileIOs) {

        mod_sst_cfg * cfg;

        unsigned int nGaussians;
        unsigned int iGaussian;
        float weight;
        float mu;
        float sigma;
        unsigned int iTrack;

        char * tmpStr1;

        cfg = mod_sst_cfg_construct();

        // +----------------------------------------------------------+
        // | Mode                                                     |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "sst.mode");

            if (strcmp(tmpStr1, "kalman") == 0) {
                cfg->mode = 'k';
            }
            else if (strcmp(tmpStr1, "particle") == 0) {
                cfg->mode = 'p';
            }
            else {
                printf("Invalid filter type.\n");
                exit(EXIT_FAILURE);
            }

            free((void *) tmpStr1);

        // +----------------------------------------------------------+
        // | nTracksMax                                               |
        // +----------------------------------------------------------+

            cfg->nTracksMax = parameters_count(fileConfig, "sst.N_inactive");

        // +----------------------------------------------------------+
        // | hopSize                                                  |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "general.size.hopSize");

        // +----------------------------------------------------------+
        // | Kalman                                                   |
        // +----------------------------------------------------------+

            cfg->sigmaQ = parameters_lookup_float(fileConfig, "sst.kalman.sigmaQ");

        // +----------------------------------------------------------+
        // | Particles                                                |
        // +----------------------------------------------------------+

            cfg->nParticles = parameters_lookup_int(fileConfig, "sst.particle.nParticles");
            cfg->st_alpha = parameters_lookup_float(fileConfig, "sst.particle.st_alpha");
            cfg->st_beta = parameters_lookup_float(fileConfig, "sst.particle.st_beta");
            cfg->st_ratio = parameters_lookup_float(fileConfig, "sst.particle.st_ratio");
            cfg->ve_alpha = parameters_lookup_float(fileConfig, "sst.particle.ve_alpha");
            cfg->ve_beta = parameters_lookup_float(fileConfig, "sst.particle.ve_beta");
            cfg->ve_ratio = parameters_lookup_float(fileConfig, "sst.particle.ve_ratio");
            cfg->ac_alpha = parameters_lookup_float(fileConfig, "sst.particle.ac_alpha");
            cfg->ac_beta = parameters_lookup_float(fileConfig, "sst.particle.ac_beta");
            cfg->ac_ratio = parameters_lookup_float(fileConfig, "sst.particle.ac_ratio");
            cfg->Nmin = parameters_lookup_float(fileConfig, "sst.particle.Nmin");

        // +----------------------------------------------------------+
        // | Epsilon                                                  |
        // +----------------------------------------------------------+

            cfg->epsilon = parameters_lookup_float(fileConfig, "general.epsilon");

        // +----------------------------------------------------------+
        // | SigmaR                                                   |
        // +----------------------------------------------------------+

            cfg->sigmaR_active = sqrtf(parameters_lookup_float(fileConfig, "sst.sigmaR2_active"));
            cfg->sigmaR_prob = sqrtf(parameters_lookup_float(fileConfig, "sst.sigmaR2_prob"));

        // +----------------------------------------------------------+
        // | GMM Active                                               |
        // +----------------------------------------------------------+            

            nGaussians = parameters_count(fileConfig, "sst.active");

            cfg->active_gmm = gaussians_1d_construct_null(nGaussians);

            for (iGaussian = 0; iGaussian < nGaussians; iGaussian++) {

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.active.[%u].weight",iGaussian);
                weight = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.active.[%u].mu",iGaussian);
                mu = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.active.[%u].sigma2",iGaussian);
                sigma = sqrtf(parameters_lookup_float(fileConfig, tmpStr1));
                free((void *) tmpStr1);

                cfg->active_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(weight, mu, sigma);
            }

        // +----------------------------------------------------------+
        // | GMM Inactive                                             |
        // +----------------------------------------------------------+  

            nGaussians = parameters_count(fileConfig, "sst.inactive");

            cfg->inactive_gmm = gaussians_1d_construct_null(nGaussians);

            for (iGaussian = 0; iGaussian < nGaussians; iGaussian++) {

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.inactive.[%u].weight",iGaussian);
                weight = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.inactive.[%u].mu",iGaussian);
                mu = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.inactive.[%u].sigma2",iGaussian);
                sigma = sqrtf(parameters_lookup_float(fileConfig, tmpStr1));
                free((void *) tmpStr1);

                cfg->inactive_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(weight, mu, sigma);
            }

        // +----------------------------------------------------------+
        // | Pfalse, Pnew and Ptrack                                  |
        // +----------------------------------------------------------+  

            cfg->Pfalse = parameters_lookup_float(fileConfig, "sst.Pfalse");
            cfg->Pnew = parameters_lookup_float(fileConfig, "sst.Pnew");
            cfg->Ptrack = parameters_lookup_float(fileConfig, "sst.Ptrack");

        // +----------------------------------------------------------+
        // | New                                                      |
        // +----------------------------------------------------------+  

            cfg->theta_new = parameters_lookup_float(fileConfig, "sst.theta_new");

        // +----------------------------------------------------------+
        // | Prob                                                     |
        // +----------------------------------------------------------+  

            cfg->theta_prob = parameters_lookup_float(fileConfig, "sst.theta_prob");
            cfg->N_prob = parameters_lookup_int(fileConfig, "sst.N_prob");

        // +----------------------------------------------------------+
        // | Inactive                                                 |
        // +----------------------------------------------------------+  

            cfg->theta_inactive = parameters_lookup_float(fileConfig, "sst.theta_inactive");
            cfg->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * cfg->nTracksMax);

            for (iTrack = 0; iTrack < cfg->nTracksMax; iTrack++) {

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.N_inactive.[%u]", iTrack);
                cfg->N_inactive[iTrack] = parameters_lookup_int(fileConfig, tmpStr1);
                free((void *) tmpStr1);

            }

        return cfg;

    }

    msg_tracks_cfg * parameters_msg_tracks_sst_config(const char * fileConfig, const char * fileIOs) {

        msg_tracks_cfg * cfg;

        cfg = msg_tracks_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        // +----------------------------------------------------------+
        // | Number of tracked sources                                |
        // +----------------------------------------------------------+

            cfg->nTracks = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    unsigned int parameters_snk_tracks_sst_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.sst");

    }

    snk_tracks_cfg * parameters_snk_tracks_sst_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_tracks_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_tracks_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.sst.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "float") == 0) { cfg->format = format_construct_float(); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.sst.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sst.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sst.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sst.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;


    }

    mod_sss_cfg * parameters_mod_sss_config(const char * fileConfig, const char * fileIOs) {

        mod_sss_cfg * cfg;

        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int iSample;
        unsigned int iLevel;

        char * tmpLabel;

        cfg = mod_sss_cfg_construct();

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            nChannels = parameters_count(fileConfig, "general.mics");

            cfg->mics = mics_construct_zero(nChannels);

            for (iChannel = 0; iChannel < nChannels; iChannel++) {

                // +--------------------------------------------------+
                // | Mu                                               |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 3; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].mu.[%u]", iChannel, iSample);
                        cfg->mics->mu[iChannel * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    }

                // +--------------------------------------------------+
                // | Sigma2                                           |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 9; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].sigma2.[%u]", iChannel, iSample);
                        cfg->mics->sigma2[iChannel * 9 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    }            

                // +--------------------------------------------------+
                // | Direction                                        |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 3; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].direction.[%u]", iChannel, iSample);
                        cfg->mics->direction[iChannel * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    } 

                // +--------------------------------------------------+
                // | Angle                                            |
                // +--------------------------------------------------+

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.mics.[%u].angle.[%u]", iChannel, 0);
                    cfg->mics->thetaAllPass[iChannel] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.mics.[%u].angle.[%u]", iChannel, 1);
                    cfg->mics->thetaNoPass[iChannel] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

            }

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->samplerate = samplerate_construct_zero();

            cfg->samplerate->mu = parameters_lookup_int(fileConfig, "general.samplerate.mu");
            cfg->samplerate->sigma2 = parameters_lookup_float(fileConfig, "general.samplerate.sigma2");

        // +----------------------------------------------------------+
        // | Sound speed                                              |
        // +----------------------------------------------------------+

            cfg->soundspeed = soundspeed_construct_zero();

            cfg->soundspeed->mu = parameters_lookup_float(fileConfig, "general.speedofsound.mu");
            cfg->soundspeed->sigma2 = parameters_lookup_float(fileConfig, "general.speedofsound.sigma2");

        // +----------------------------------------------------------+
        // | Directivity                                              |
        // +----------------------------------------------------------+

            cfg->nThetas = parameters_lookup_int(fileConfig, "sss.nThetas");
            cfg->gainMin = parameters_lookup_float(fileConfig, "sss.gainMin");

        return cfg;

    }

    msg_spectra_cfg * parameters_msg_spectra_sss_config(const char * fileConfig, const char * fileIOs) {

        msg_spectra_cfg * cfg;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        cfg = msg_spectra_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->halfFrameSize = parameters_lookup_int(fileConfig, "general.size.frameSize") / 2 + 1;

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;


    }

    unsigned int parameters_snk_spectra_sss_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.sss");

    }

    snk_spectra_cfg * parameters_snk_spectra_sss_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_spectra_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_spectra_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.sss.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "float") == 0) { cfg->format = format_construct_float(); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.sss.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sss.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sss.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sss.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    mod_sspf_cfg * parameters_mod_sspf_config(const char * fileConfig, const char * fileIOs) {

        mod_sspf_cfg * cfg;

        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int iSample;
        unsigned int iLevel;

        char * tmpLabel;

        cfg = mod_sspf_cfg_construct();

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            nChannels = parameters_count(fileConfig, "general.mics");

            cfg->mics = mics_construct_zero(nChannels);

            for (iChannel = 0; iChannel < nChannels; iChannel++) {

                // +--------------------------------------------------+
                // | Mu                                               |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 3; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].mu.[%u]", iChannel, iSample);
                        cfg->mics->mu[iChannel * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    }

                // +--------------------------------------------------+
                // | Sigma2                                           |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 9; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].sigma2.[%u]", iChannel, iSample);
                        cfg->mics->sigma2[iChannel * 9 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    }            

                // +--------------------------------------------------+
                // | Direction                                        |
                // +--------------------------------------------------+

                    for (iSample = 0; iSample < 3; iSample++) {

                        tmpLabel = (char *) malloc(sizeof(char) * 1024);
                        sprintf(tmpLabel, "general.mics.[%u].direction.[%u]", iChannel, iSample);
                        cfg->mics->direction[iChannel * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                        free((void *) tmpLabel);

                    } 

                // +--------------------------------------------------+
                // | Angle                                            |
                // +--------------------------------------------------+

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.mics.[%u].angle.[%u]", iChannel, 0);
                    cfg->mics->thetaAllPass[iChannel] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.mics.[%u].angle.[%u]", iChannel, 1);
                    cfg->mics->thetaNoPass[iChannel] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

            }

        // +----------------------------------------------------------+
        // | Epsilon                                                  |
        // +----------------------------------------------------------+

            cfg->epsilon = parameters_lookup_float(fileConfig, "general.epsilon");

        // +----------------------------------------------------------+
        // | Directivity                                              |
        // +----------------------------------------------------------+

            cfg->nThetas = parameters_lookup_int(fileConfig, "sspf.nThetas");
            cfg->gainMin = parameters_lookup_float(fileConfig, "sspf.gainMin");

        return cfg;

    }

    msg_spectra_cfg * parameters_msg_spectra_sspf_config(const char * fileConfig, const char * fileIOs) {

        msg_spectra_cfg * cfg;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        cfg = msg_spectra_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->halfFrameSize = parameters_lookup_int(fileConfig, "general.size.frameSize") / 2 + 1;

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    unsigned int parameters_snk_spectra_sspf_count(const char * fileConfig, const char * fileIOs) {

        return parameters_count(fileIOs, "output.sspf");

    }

    snk_spectra_cfg * parameters_snk_spectra_sspf_config(const char * fileConfig, const char * fileIOs, const unsigned int iSink) {

        snk_spectra_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        char * tmpLabel;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = snk_spectra_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.sspf.[%u].format", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "float") == 0) { cfg->format = format_construct_float(); }
            else { printf("Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpLabel = (char *) malloc(sizeof(char) * 1024);
            sprintf(tmpLabel, "output.sspf.[%u].type", iSink);
            tmpStr1 = parameters_lookup_string(fileIOs, tmpLabel);
            free((void *) tmpLabel);

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sspf.[%u].path", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sspf.[%u].ip", iSink);
                tmpStr2 = parameters_lookup_string(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "output.sspf.[%u].port", iSink);
                tmpInt1 = parameters_lookup_int(fileIOs, tmpLabel);
                free((void *) tmpLabel);

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else {

                printf("Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }