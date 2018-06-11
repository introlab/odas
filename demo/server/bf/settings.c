
	#include "settings.h"

	settings * settings_construct(const char * file) {

		settings * sets;
		config_t cfg;
		config_setting_t * cfg_setting;

		char s[1024];
		unsigned int n;
		unsigned int N;
		unsigned int d;

		sets = (settings *) malloc(sizeof(settings));

        config_init(&cfg); 

        if(!config_read_file(&cfg, file))
        {
            
            printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
          
            exit(EXIT_FAILURE);

        }       

        sets->general.epsilon = config_setting_get_float(settings_lookup(&cfg, "general.epsilon"));
        sets->general.size.hopSize = config_setting_get_int(settings_lookup(&cfg, "general.size.hopSize"));
        sets->general.size.frameSize = config_setting_get_int(settings_lookup(&cfg, "general.size.frameSize"));
        sets->general.samplerate.mu = config_setting_get_int(settings_lookup(&cfg, "general.samplerate.mu"));
        sets->general.samplerate.sigma2 = config_setting_get_float(settings_lookup(&cfg, "general.samplerate.sigma2"));
        sets->general.speedofsound.mu = config_setting_get_float(settings_lookup(&cfg, "general.speedofsound.mu"));
        sets->general.speedofsound.sigma2 = config_setting_get_float(settings_lookup(&cfg, "general.speedofsound.sigma2"));

        N = config_setting_length(settings_lookup(&cfg, "general.mics"));
        sets->general.mics.N = N;

        for (n = 0; n < N; n++) {

        	for (d = 0; d < 3; d++) {
        		sprintf(s, "general.mics.[%u].mu.[%u]", n, d);
        		sets->general.mics.array[n].mu[d] = config_setting_get_float(settings_lookup(&cfg, s));
        	}

        	for (d = 0; d < 9; d++) {
        		sprintf(s, "general.mics.[%u].sigma2.[%u]", n, d);
        		sets->general.mics.array[n].sigma2[d] = config_setting_get_float(settings_lookup(&cfg, s));
        	}

        	for (d = 0; d < 3; d++) {
        		sprintf(s, "general.mics.[%u].direction.[%u]", n, d);
        		sets->general.mics.array[n].direction[d] = config_setting_get_float(settings_lookup(&cfg, s));
        	}

        	for (d = 0; d < 2; d++) {
        		sprintf(s, "general.mics.[%u].angle.[%u]", n, d);
        		sets->general.mics.array[n].angle[d] = config_setting_get_float(settings_lookup(&cfg, s));
        	}

        }

        N = config_setting_length(settings_lookup(&cfg, "general.spatialfilters"));
        sets->general.spatialfilters.N = N;

        for (n = 0; n < N; n++) {

        	for (d = 0; d < 3; d++) {
        		sprintf(s, "general.spatialfilters.[%u].direction.[%u]", n, d);
        		sets->general.spatialfilters.array[n].direction[d] = config_setting_get_float(settings_lookup(&cfg, s));
        	}

        	for (d = 0; d < 2; d++) {
        		sprintf(s, "general.spatialfilters.[%u].angle.[%u]", n, d);
        		sets->general.spatialfilters.array[n].angle[d] = config_setting_get_float(settings_lookup(&cfg, s));
        	}

        }

        sets->general.nThetas = config_setting_get_int(settings_lookup(&cfg, "general.nThetas"));
        sets->general.gainMin = config_setting_get_float(settings_lookup(&cfg, "general.gainMin"));

        sets->bf.nSrcs = config_setting_get_int(settings_lookup(&cfg, "bf.nSrcs"));
        strcpy(sets->bf.mode, config_setting_get_string(settings_lookup(&cfg, "bf.mode")));

        config_destroy(&cfg);   

		return sets;

	}

	void settings_destroy(settings * sets) {

		free((void *) sets);

	}

	void settings_printf(const settings * sets) {

		unsigned int n;
		unsigned int d;

		printf("general.epsilon = %e\n", sets->general.epsilon);
		printf("general.size.hopSize = %u\n", sets->general.size.hopSize);
		printf("general.size.frameSize = %u\n", sets->general.size.frameSize);
		printf("general.samplerate.mu = %u\n", sets->general.samplerate.mu);
		printf("general.samplerate.sigma2 = %f\n", sets->general.samplerate.sigma2);
		printf("general.speedofsound.mu = %f\n", sets->general.speedofsound.mu);
		printf("general.speedofsound.sigma2 = %f\n", sets->general.speedofsound.sigma2);

		for (n = 0; n < sets->general.mics.N; n++) {

			printf("general.mics[%u].mu = [ ", n);
			for (d = 0; d < 3; d++) {
				printf("%f ", sets->general.mics.array[n].mu[d]);
			}
			printf("]\n");

			printf("general.mics[%u].sigma2 = [ ", n);
			for (d = 0; d < 9; d++) {
				printf("%f ", sets->general.mics.array[n].sigma2[d]);
			}
			printf("]\n");

			printf("general.mics[%u].direction = [ ", n);
			for (d = 0; d < 3; d++) {
				printf("%f ", sets->general.mics.array[n].direction[d]);
			}
			printf("]\n");

			printf("general.mics[%u].angle = [ ", n);
			for (d = 0; d < 2; d++) {
				printf("%f ", sets->general.mics.array[n].angle[d]);
			}
			printf("]\n");

		}

		for (n = 0; n < sets->general.spatialfilters.N; n++) {

			printf("general.spatialfilters[%u].direction = [ ", n);
			for (d = 0; d < 3; d++) {
				printf("%f ", sets->general.spatialfilters.array[n].direction[d]);
			}
			printf("]\n");

			printf("general.spatialfilters[%u].angle = [ ", n);
			for (d = 0; d < 2; d++) {
				printf("%f ", sets->general.spatialfilters.array[n].angle[d]);
			}
			printf("]\n");			

		}

		printf("general.nThetas = %u\n", sets->general.nThetas);
		printf("general.gainMin = %f\n", sets->general.gainMin);

		printf("bf.nSrcs = %u\n", sets->bf.nSrcs);
		printf("bf.mode = %s\n", sets->bf.mode);

	}

	config_setting_t * settings_lookup(const config_t * cfg, const char * s) {

		config_setting_t * cfg_set;

        cfg_set = config_lookup(cfg, s);

        if (cfg_set == NULL) { 

        	printf("Error loading %s\n", s); 
        	exit(EXIT_FAILURE); 

       	};

       	return cfg_set;

	}