
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

    src_hops_cfg * parameters_src_hops_mics_config(const char * fileConfig) {

        src_hops_cfg * cfg;
        char * tmpStr1;
        char * tmpStr2;
        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = src_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpInt1 = parameters_lookup_int(fileConfig, "raw.nBits");

            if ((tmpInt1 == 8) || (tmpInt1 == 16) || (tmpInt1 == 24) || (tmpInt1 == 32)) {
                cfg->format = format_construct_binary_int(tmpInt1);
            }
            else {
                printf("raw.nBits: Invalid number of bits\n");
                exit(EXIT_FAILURE);
            }

        // +----------------------------------------------------------+
        // | Interface                                                |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "raw.interface.type");

            if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "raw.interface.path");

                cfg->interface = interface_construct_file(tmpStr2);

                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "raw.interface.ip");
                tmpInt1 = parameters_lookup_int(fileConfig, "raw.interface.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);

                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "soundcard") == 0) {

                tmpInt1 = parameters_lookup_int(fileConfig, "raw.interface.card");
                tmpInt2 = parameters_lookup_int(fileConfig, "raw.interface.device");

                cfg->interface = interface_construct_soundcard(tmpInt1, tmpInt2);

            }
            else if (strcmp(tmpStr1, "soundcard_name") == 0) {

                tmpStr2 = parameters_lookup_string(fileConfig, "raw.interface.devicename");

                cfg->interface = interface_construct_soundcard_by_name(tmpStr2);

            }
            else {
                printf("raw.interface.type: Invalid type\n");
                exit(EXIT_FAILURE);
            }

            free((void *) tmpStr1);

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_mics_raw_config(const char * fileConfig) {

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


    mod_mapping_cfg * parameters_mod_mapping_mics_config(const char * fileConfig) {

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

    msg_hops_cfg * parameters_msg_hops_mics_map_config(const char * fileConfig) {

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

    mod_resample_cfg * parameters_mod_resample_mics_config(const char * fileConfig) {

        mod_resample_cfg * cfg;

        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = mod_resample_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rates                                             |
        // +----------------------------------------------------------+

            tmpInt1 = parameters_lookup_int(fileConfig, "raw.fS");        
            tmpInt2 = parameters_lookup_int(fileConfig, "general.samplerate.mu");              

            if (tmpInt1 < tmpInt2) {
                printf("general.samplerate.mu: This sample rate must be smaller or equal to raw.fS");
                exit(EXIT_FAILURE);
            }

            cfg->fSin = tmpInt1;
            cfg->fSout = tmpInt2;

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_mics_rs_config(const char * fileConfig) {

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

    mod_stft_cfg * parameters_mod_stft_mics_config(const char * fileConfig) {

        mod_stft_cfg * cfg;

        cfg = mod_stft_cfg_construct();

        return cfg;

    }

    msg_spectra_cfg * parameters_msg_spectra_mics_config(const char * fileConfig) {

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

    mod_noise_cfg * parameters_mod_noise_mics_config(const char * fileConfig) {

        mod_noise_cfg * cfg;

        cfg = mod_noise_cfg_construct();

        // +----------------------------------------------------------+
        // | Hanning window size                                      |
        // +----------------------------------------------------------+

            cfg->bSize = parameters_lookup_int(fileConfig, "sne.b");

        // +----------------------------------------------------------+
        // | alphaS                                                   |
        // +----------------------------------------------------------+

            cfg->alphaS = parameters_lookup_float(fileConfig, "sne.alphaS");

        // +----------------------------------------------------------+
        // | Number of frames                                         |
        // +----------------------------------------------------------+

            cfg->L = parameters_lookup_int(fileConfig, "sne.L");

        // +----------------------------------------------------------+
        // | delta                                                    |
        // +----------------------------------------------------------+

            cfg->delta = parameters_lookup_float(fileConfig, "sne.delta");

        // +----------------------------------------------------------+
        // | alphaD                                                   |
        // +----------------------------------------------------------+

            cfg->alphaD = parameters_lookup_float(fileConfig, "sne.alphaD");            

        return cfg;

    }

    msg_powers_cfg * parameters_msg_powers_mics_config(const char * fileConfig) {

        msg_powers_cfg * cfg;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        cfg = msg_powers_cfg_construct();

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

    mod_ssl_cfg * parameters_mod_ssl_config(const char * fileConfig) {

        mod_ssl_cfg * cfg;

        unsigned int nChannels;
        unsigned int nFilters;
        unsigned int iChannel;
        unsigned int iFilter;
        unsigned int iSample;
        unsigned int iLevel;

        char * tmpLabel;
        char * tmpString;

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
        // | Interpolation                                            |
        // +----------------------------------------------------------+

            cfg->interpRate = parameters_lookup_int(fileConfig, "ssl.interpRate");

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

            cfg->nThetas = parameters_lookup_int(fileConfig, "general.nThetas");

        // +----------------------------------------------------------+
        // | Number of thetas                                         |
        // +----------------------------------------------------------+

            cfg->gainMin = parameters_lookup_float(fileConfig, "general.gainMin");

        // +----------------------------------------------------------+
        // | Spatial filter                                           |
        // +----------------------------------------------------------+

            nFilters = parameters_count(fileConfig, "general.spatialfilters");

            cfg->spatialfilters = spatialfilters_construct_zero(nFilters);

            for (iFilter = 0; iFilter < nFilters; iFilter++) {

                // +--------------------------------------------------+
                // | Direction                                        |
                // +--------------------------------------------------+

                for (iSample = 0; iSample < 3; iSample++) {

                    tmpLabel = (char *) malloc(sizeof(char) * 1024);
                    sprintf(tmpLabel, "general.spatialfilters.[%u].direction.[%u]", iFilter, iSample);
                    cfg->spatialfilters->direction[iFilter * 3 + iSample] = parameters_lookup_float(fileConfig, tmpLabel);
                    free((void *) tmpLabel);

                }

                // +--------------------------------------------------+
                // | thetaAllPass                                     |
                // +--------------------------------------------------+

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "general.spatialfilters.[%u].angle.[0]", iFilter);
                cfg->spatialfilters->thetaAllPass[iFilter] = parameters_lookup_float(fileConfig, tmpLabel);
                free((void *) tmpLabel);

                // +--------------------------------------------------+
                // | thetaNoPass                                      |
                // +--------------------------------------------------+

                tmpLabel = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpLabel, "general.spatialfilters.[%u].angle.[1]", iFilter);
                cfg->spatialfilters->thetaNoPass[iFilter] = parameters_lookup_float(fileConfig, tmpLabel);
                free((void *) tmpLabel);

            }

        return cfg;

    }

    msg_pots_cfg * parameters_msg_pots_ssl_config(const char * fileConfig) {

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

    snk_pots_cfg * parameters_snk_pots_ssl_config(const char * fileConfig) {

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

            tmpStr1 = parameters_lookup_string(fileConfig, "ssl.potential.format");

            if (strcmp(tmpStr1, "json") == 0) { cfg->format = format_construct_text_json(); }
            else if (strcmp(tmpStr1, "binary") == 0) { cfg->format = format_construct_binary_float(); }
            else if (strcmp(tmpStr1, "undefined") == 0) { cfg->format = format_construct_undefined(); }
            else { printf("ssl.potential.format: Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Interface                                                |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "ssl.potential.interface.type");

            if (strcmp(tmpStr1, "blackhole") == 0) {

                cfg->interface = interface_construct_blackhole();

            }
            else if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "ssl.potential.interface.path");
                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "ssl.potential.interface.ip");
                tmpInt1 = parameters_lookup_int(fileConfig, "ssl.potential.interface.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "terminal") == 0) {

                cfg->interface = interface_construct_terminal();               

            }
            else {

                printf("ssl.potential.interface.type: Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    inj_targets_cfg * parameters_inj_targets_sst_config(const char * fileConfig) {

        inj_targets_cfg * cfg;
        unsigned int iTarget;
        unsigned int nTargets;
        float x, y, z;        
        char * tmpStr1;
        char * tmpStr2;

        cfg = inj_targets_cfg_construct();

        // +----------------------------------------------------------+
        // | Number of targets                                        |
        // +----------------------------------------------------------+        

            nTargets = parameters_count(fileConfig, "sst.target");      

            cfg->nTargets = nTargets;

        // +----------------------------------------------------------+
        // | Targets                                                  |
        // +----------------------------------------------------------+        

            cfg->targets = targets_construct_zero(nTargets);

            for (iTarget = 0; iTarget < nTargets; iTarget++) {

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.target.[%u].tag",iTarget);
                tmpStr2 = parameters_lookup_string(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.target.[%u].x",iTarget);
                x = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.target.[%u].y",iTarget);
                y = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);

                tmpStr1 = (char *) malloc(sizeof(char) * 1024);
                sprintf(tmpStr1, "sst.target.[%u].z",iTarget);
                z = parameters_lookup_float(fileConfig, tmpStr1);
                free((void *) tmpStr1);                

                strcpy(cfg->targets->tags[iTarget],tmpStr2);
                cfg->targets->array[iTarget *3 + 0] = x;
                cfg->targets->array[iTarget *3 + 1] = y;
                cfg->targets->array[iTarget *3 + 2] = z;

                free((void *) tmpStr2);

            }

        return cfg;

    }

    msg_targets_cfg * parameters_msg_targets_sst_config(const char * fileConfig) {

        msg_targets_cfg * cfg;
        unsigned int nTargets;

        cfg = msg_targets_cfg_construct();

        // +----------------------------------------------------------+
        // | Number of targets                                        |
        // +----------------------------------------------------------+        

            nTargets = parameters_count(fileConfig, "sst.target");      

            cfg->nTargets = nTargets;

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");              

        return cfg;

    }

    mod_sst_cfg * parameters_mod_sst_config(const char * fileConfig) {

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
                printf("sst.mode: Invalid filter type.\n");
                exit(EXIT_FAILURE);
            }

            free((void *) tmpStr1);

        // +----------------------------------------------------------+
        // | Add                                                      |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "sst.add");

            if (strcmp(tmpStr1, "dynamic") == 0) {
                cfg->add = 'd';
            }
            else if (strcmp(tmpStr1, "static") == 0) {
                cfg->add = 's';
            }
            else {
                printf("sst.add: Invalid add type.\n");
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
            cfg->sigmaR_target = sqrtf(parameters_lookup_float(fileConfig, "sst.sigmaR2_target"));

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

    msg_tracks_cfg * parameters_msg_tracks_sst_config(const char * fileConfig) {

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

    snk_tracks_cfg * parameters_snk_tracks_sst_config(const char * fileConfig) {

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

            tmpStr1 = parameters_lookup_string(fileConfig, "sst.tracked.format");

            if (strcmp(tmpStr1, "json") == 0) { cfg->format = format_construct_text_json(); }
            else if (strcmp(tmpStr1, "binary") == 0) { cfg->format = format_construct_binary_float(); }
            else if (strcmp(tmpStr1, "undefined") == 0) { cfg->format = format_construct_undefined(); }            
            else { printf("sst.tracked.format: Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Interface                                                |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "sst.tracked.interface.type");

            if (strcmp(tmpStr1, "blackhole") == 0) {

                cfg->interface = interface_construct_blackhole();

            }
            else if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "sst.tracked.interface.path");
                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "sst.tracked.interface.ip");
                tmpInt1 = parameters_lookup_int(fileConfig, "sst.tracked.interface.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "terminal") == 0) {

                cfg->interface = interface_construct_terminal();               

            }
            else {

                printf("sst.tracked.interface.type: Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;


    }

    mod_sss_cfg * parameters_mod_sss_config(const char * fileConfig) {

        mod_sss_cfg * cfg;

        unsigned int nChannels;
        unsigned int iChannel;
        unsigned int iSample;

        char * tmpStr1;
        char * tmpLabel;

        cfg = mod_sss_cfg_construct();

        // +----------------------------------------------------------+
        // | Mode                                                     |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "sss.mode_sep");

            if (strcmp(tmpStr1, "dds") == 0) {
                cfg->mode_sep = 'd';
            }
            else if (strcmp(tmpStr1, "dgss") == 0) {
                cfg->mode_sep = 'g';
            }
            else if (strcmp(tmpStr1, "dmvdr") == 0) {
                cfg->mode_sep = 'm';
            }            
            else {
                printf("sss.mode_sep: Invalid separation method.\n");
                exit(EXIT_FAILURE);
            }

            free((void *) tmpStr1);

            tmpStr1 = parameters_lookup_string(fileConfig, "sss.mode_pf");

            if (strcmp(tmpStr1, "ms") == 0) {
                cfg->mode_pf = 'm';
            }
            else if (strcmp(tmpStr1, "ss") == 0) {
                cfg->mode_pf = 's';
            }
            else {
                printf("sss.mode_pf: Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);
            }

            free((void *) tmpStr1);

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
        // | Number of thetas                                         |
        // +----------------------------------------------------------+

            cfg->nThetas = parameters_lookup_int(fileConfig, "general.nThetas");

        // +----------------------------------------------------------+
        // | Number of thetas                                         |
        // +----------------------------------------------------------+

            cfg->gainMin = parameters_lookup_float(fileConfig, "general.gainMin");

        // +----------------------------------------------------------+
        // | Epsilon                                                  |
        // +----------------------------------------------------------+

            cfg->epsilon = parameters_lookup_float(fileConfig, "general.epsilon");

        // +----------------------------------------------------------+
        // | Mu                                                       |
        // +----------------------------------------------------------+

            cfg->sep_gss_mu = parameters_lookup_float(fileConfig, "sss.dgss.mu");

        // +----------------------------------------------------------+
        // | Lambda                                                   |
        // +----------------------------------------------------------+

            cfg->sep_gss_lambda = parameters_lookup_float(fileConfig, "sss.dgss.lambda");

        // +----------------------------------------------------------+
        // | Hanning window size                                      |
        // +----------------------------------------------------------+

            cfg->pf_ms_bSize = parameters_lookup_int(fileConfig, "sne.b");

        // +----------------------------------------------------------+
        // | alphaS                                                   |
        // +----------------------------------------------------------+

            cfg->pf_ms_alphaS = parameters_lookup_float(fileConfig, "sne.alphaS");

        // +----------------------------------------------------------+
        // | Number of frames                                         |
        // +----------------------------------------------------------+

            cfg->pf_ms_L = parameters_lookup_int(fileConfig, "sne.L");

        // +----------------------------------------------------------+
        // | delta                                                    |
        // +----------------------------------------------------------+

            cfg->pf_ms_delta = parameters_lookup_float(fileConfig, "sne.delta");

        // +----------------------------------------------------------+
        // | alphaD                                                   |
        // +----------------------------------------------------------+

            cfg->pf_ms_alphaD = parameters_lookup_float(fileConfig, "sne.alphaD");  

        // +----------------------------------------------------------+
        // | eta                                                      |
        // +----------------------------------------------------------+

            cfg->pf_ms_eta = parameters_lookup_float(fileConfig, "sss.ms.eta");

        // +----------------------------------------------------------+
        // | alphaZ                                                |
        // +----------------------------------------------------------+

            cfg->pf_ms_alphaZ = parameters_lookup_float(fileConfig, "sss.ms.alphaZ");

        // +----------------------------------------------------------+
        // | alphaPmin                                                |
        // +----------------------------------------------------------+

            cfg->pf_ms_alphaPmin = parameters_lookup_float(fileConfig, "sss.ms.alphaPmin");

        // +----------------------------------------------------------+
        // | thetaWin                                                 |
        // +----------------------------------------------------------+

            cfg->pf_ms_thetaWin = parameters_lookup_float(fileConfig, "sss.ms.thetaWin");

        // +----------------------------------------------------------+
        // | alphaWin                                                 |
        // +----------------------------------------------------------+

            cfg->pf_ms_alphaWin = parameters_lookup_float(fileConfig, "sss.ms.alphaWin");

        // +----------------------------------------------------------+
        // | maxAbsenceProb                                           |
        // +----------------------------------------------------------+

            cfg->pf_ms_maxAbsenceProb = parameters_lookup_float(fileConfig, "sss.ms.maxAbsenceProb");

        // +----------------------------------------------------------+
        // | Gmin                                                     |
        // +----------------------------------------------------------+

            cfg->pf_ms_Gmin = parameters_lookup_float(fileConfig, "sss.ms.Gmin");

        // +----------------------------------------------------------+
        // | winSizeLocal                                             |
        // +----------------------------------------------------------+

            cfg->pf_ms_winSizeLocal = parameters_lookup_int(fileConfig, "sss.ms.winSizeLocal");

        // +----------------------------------------------------------+
        // | winSizeGlobal                                            |
        // +----------------------------------------------------------+

            cfg->pf_ms_winSizeGlobal = parameters_lookup_int(fileConfig, "sss.ms.winSizeGlobal");

        // +----------------------------------------------------------+
        // | winSizeFrame                                             |
        // +----------------------------------------------------------+

            cfg->pf_ms_winSizeFrame = parameters_lookup_int(fileConfig, "sss.ms.winSizeFrame");

        // +----------------------------------------------------------+
        // | Gmin                                                     |
        // +----------------------------------------------------------+

            cfg->pf_ss_Gmin = parameters_lookup_float(fileConfig, "sss.ss.Gmin");

        // +----------------------------------------------------------+
        // | Gmid                                                     |
        // +----------------------------------------------------------+

            cfg->pf_ss_Gmid = parameters_lookup_float(fileConfig, "sss.ss.Gmid");

        // +----------------------------------------------------------+
        // | Gslope                                                   |
        // +----------------------------------------------------------+

            cfg->pf_ss_Gslope = parameters_lookup_float(fileConfig, "sss.ss.Gslope");

        return cfg;      

    }

    msg_spectra_cfg * parameters_msg_spectra_seps_config(const char * fileConfig) {

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
        // | Half frame size                                          |
        // +----------------------------------------------------------+

            cfg->halfFrameSize = parameters_lookup_int(fileConfig, "general.size.frameSize") / 2 + 1;

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    msg_spectra_cfg * parameters_msg_spectra_pfs_config(const char * fileConfig) {

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
        // | Half frame size                                          |
        // +----------------------------------------------------------+

            cfg->halfFrameSize = parameters_lookup_int(fileConfig, "general.size.frameSize") / 2 + 1;

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }    

    mod_istft_cfg * parameters_mod_istft_seps_config(const char * fileConfig) {

        mod_istft_cfg * cfg;

        cfg = mod_istft_cfg_construct();

        return cfg;

    }

    mod_istft_cfg * parameters_mod_istft_pfs_config(const char * fileConfig) {

        mod_istft_cfg * cfg;

        cfg = mod_istft_cfg_construct();

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_seps_config(const char * fileConfig) {

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

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_pfs_config(const char * fileConfig) {

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

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    mod_resample_cfg * parameters_mod_resample_seps_config(const char * fileConfig) {

        mod_resample_cfg * cfg;

        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = mod_resample_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rates                                             |
        // +----------------------------------------------------------+

            tmpInt1 = parameters_lookup_int(fileConfig, "general.samplerate.mu");        
            tmpInt2 = parameters_lookup_int(fileConfig, "sss.separated.fS");              

            cfg->fSin = tmpInt1;
            cfg->fSout = tmpInt2;

        return cfg;

    }

    mod_resample_cfg * parameters_mod_resample_pfs_config(const char * fileConfig) {

        mod_resample_cfg * cfg;

        unsigned int tmpInt1;
        unsigned int tmpInt2;

        cfg = mod_resample_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rates                                             |
        // +----------------------------------------------------------+

            tmpInt1 = parameters_lookup_int(fileConfig, "general.samplerate.mu");        
            tmpInt2 = parameters_lookup_int(fileConfig, "sss.postfiltered.fS");              

            cfg->fSin = tmpInt1;
            cfg->fSout = tmpInt2;

        return cfg;

    }    

    msg_hops_cfg * parameters_msg_hops_seps_rs_config(const char * fileConfig) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "sss.separated.fS");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "sss.separated.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_pfs_rs_config(const char * fileConfig) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "sss.postfiltered.fS");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "sss.postfiltered.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }    

    mod_volume_cfg * parameters_mod_volume_seps_config(const char * fileConfig) {

        mod_volume_cfg * cfg;

        cfg = mod_volume_cfg_construct();

        // +----------------------------------------------------------+
        // | Gain                                                     |
        // +----------------------------------------------------------+

            cfg->gain = parameters_lookup_float(fileConfig, "sss.gain_sep");

        return cfg;

    }

    mod_volume_cfg * parameters_mod_volume_pfs_config(const char * fileConfig) {

        mod_volume_cfg * cfg;

        cfg = mod_volume_cfg_construct();

        // +----------------------------------------------------------+
        // | Gain                                                     |
        // +----------------------------------------------------------+

            cfg->gain = parameters_lookup_float(fileConfig, "sss.gain_pf");

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_seps_vol_config(const char * fileConfig) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "sss.separated.fS");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "sss.separated.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    msg_hops_cfg * parameters_msg_hops_pfs_vol_config(const char * fileConfig) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "sss.postfiltered.fS");        

        // +----------------------------------------------------------+
        // | Hop size                                                 |
        // +----------------------------------------------------------+

            cfg->hopSize = parameters_lookup_int(fileConfig, "sss.postfiltered.hopSize");

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");

        return cfg;

    }

    snk_hops_cfg * parameters_snk_hops_seps_vol_config(const char * fileConfig) {

        snk_hops_cfg * cfg;
        unsigned int tmpInt1;
        char * tmpStr1;
        char * tmpStr2;

        cfg = snk_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "sss.separated.fS");


        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpInt1 = parameters_lookup_int(fileConfig, "sss.separated.nBits");

            if ((tmpInt1 == 8) || (tmpInt1 == 16) || (tmpInt1 == 24) || (tmpInt1 == 32)) {
                cfg->format = format_construct_binary_int(tmpInt1);
            }
            else {
                printf("raw.nBits: Invalid number of bits\n");
                exit(EXIT_FAILURE);
            }    

        // +----------------------------------------------------------+
        // | Interface                                                |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "sss.separated.interface.type");

            if (strcmp(tmpStr1, "blackhole") == 0) {

                cfg->interface = interface_construct_blackhole();
                cfg->format = format_construct_undefined();

            }
            else if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "sss.separated.interface.path");
                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "sss.separated.interface.ip");
                tmpInt1 = parameters_lookup_int(fileConfig, "sss.separated.interface.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "terminal") == 0) {

                cfg->interface = interface_construct_terminal();               

            }
            else {

                printf("sss.separated.interface.type: Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    snk_hops_cfg * parameters_snk_hops_pfs_vol_config(const char * fileConfig) {

        snk_hops_cfg * cfg;
        unsigned int tmpInt1;
        char * tmpStr1;
        char * tmpStr2;

        cfg = snk_hops_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "sss.postfiltered.fS");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpInt1 = parameters_lookup_int(fileConfig, "sss.postfiltered.nBits");

            if ((tmpInt1 == 8) || (tmpInt1 == 16) || (tmpInt1 == 24) || (tmpInt1 == 32)) {
                cfg->format = format_construct_binary_int(tmpInt1);
            }
            else {
                printf("raw.nBits: Invalid number of bits\n");
                exit(EXIT_FAILURE);
            }    

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "sss.postfiltered.interface.type");

            if (strcmp(tmpStr1, "blackhole") == 0) {

                cfg->interface = interface_construct_blackhole();
                cfg->format = format_construct_undefined();

            }
            else if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "sss.postfiltered.interface.path");
                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "sss.postfiltered.interface.ip");
                tmpInt1 = parameters_lookup_int(fileConfig, "sss.postfiltered.interface.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "terminal") == 0) {

                cfg->interface = interface_construct_terminal();               

            }
            else {

                printf("sss.postfiltered.interface.type: Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }

    mod_classify_cfg * parameters_mod_classify_config(const char * fileConfig) {

        mod_classify_cfg * cfg;

        cfg = mod_classify_cfg_construct();

        // +----------------------------------------------------------+
        // | Frame size                                               |
        // +----------------------------------------------------------+

            cfg->frameSize = parameters_lookup_int(fileConfig, "classify.frameSize");

        // +----------------------------------------------------------+
        // | Window size                                              |
        // +----------------------------------------------------------+

            cfg->winSize = parameters_lookup_int(fileConfig, "classify.winSize");

        // +----------------------------------------------------------+
        // | tauMin                                                   |
        // +----------------------------------------------------------+

            cfg->tauMin = parameters_lookup_int(fileConfig, "classify.tauMin");

        // +----------------------------------------------------------+
        // | tauMax                                                   |
        // +----------------------------------------------------------+

            cfg->tauMax = parameters_lookup_int(fileConfig, "classify.tauMax");

        // +----------------------------------------------------------+
        // | deltaTauMax                                              |
        // +----------------------------------------------------------+

            cfg->deltaTauMax = parameters_lookup_int(fileConfig, "classify.deltaTauMax");

        // +----------------------------------------------------------+
        // | alpha                                                    |
        // +----------------------------------------------------------+

            cfg->alpha = parameters_lookup_float(fileConfig, "classify.alpha");

        // +----------------------------------------------------------+
        // | gamma                                                    |
        // +----------------------------------------------------------+

            cfg->gamma = parameters_lookup_float(fileConfig, "classify.gamma");

        // +----------------------------------------------------------+
        // | phiMin                                                   |
        // +----------------------------------------------------------+

            cfg->phiMin = parameters_lookup_float(fileConfig, "classify.phiMin");

        // +----------------------------------------------------------+
        // | r0                                                       |
        // +----------------------------------------------------------+           

            cfg->r0 = parameters_lookup_float(fileConfig, "classify.r0");

        return cfg;

    }

    msg_categories_cfg * parameters_msg_categories_config(const char * fileConfig) {

        msg_categories_cfg * cfg;

        cfg = msg_categories_cfg_construct();

        // +----------------------------------------------------------+
        // | Number of channels                                       |
        // +----------------------------------------------------------+

            cfg->nChannels = parameters_count(fileConfig, "sst.N_inactive");        

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");  

        return cfg;

    }

    snk_categories_cfg * parameters_snk_categories_config(const char * fileConfig) {

        snk_categories_cfg * cfg;
        unsigned int tmpInt1;
        char * tmpStr1;
        char * tmpStr2;

        cfg = snk_categories_cfg_construct();

        // +----------------------------------------------------------+
        // | Sample rate                                              |
        // +----------------------------------------------------------+

            cfg->fS = parameters_lookup_int(fileConfig, "general.samplerate.mu");

        // +----------------------------------------------------------+
        // | Format                                                   |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "classify.category.format");

            if (strcmp(tmpStr1, "json") == 0) { cfg->format = format_construct_text_json(); }
            else if (strcmp(tmpStr1, "undefined") == 0) { cfg->format = format_construct_undefined(); }                       
            else { printf("classify.category.format: Invalid format\n"); exit(EXIT_FAILURE); }

            free((void *) tmpStr1);       

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            tmpStr1 = parameters_lookup_string(fileConfig, "classify.category.interface.type");

            if (strcmp(tmpStr1, "blackhole") == 0) {

                cfg->interface = interface_construct_blackhole();

            }
            else if (strcmp(tmpStr1, "file") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "classify.category.interface.path");
                cfg->interface = interface_construct_file(tmpStr2);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "socket") == 0) { 

                tmpStr2 = parameters_lookup_string(fileConfig, "classify.category.interface.ip");
                tmpInt1 = parameters_lookup_int(fileConfig, "classify.category.interface.port");

                cfg->interface = interface_construct_socket(tmpStr2, tmpInt1);
                free((void *) tmpStr2);

            }
            else if (strcmp(tmpStr1, "terminal") == 0) {

                cfg->interface = interface_construct_terminal();               

            }
            else {

                printf("classify.category.interface.type: Invalid type\n");
                exit(EXIT_FAILURE);

            }

            free((void *) tmpStr1);

        return cfg;

    }