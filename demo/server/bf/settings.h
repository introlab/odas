#ifndef __ODASSERVERBF_SETTINGS
#define __ODASSERVERBF_SETTINGS

	#include <stdlib.h>
	#include <string.h>
	#include <libconfig.h>

	typedef struct settings_size {

		unsigned int hopSize;
		unsigned int frameSize;

	} settings_size;

	typedef struct settings_samplerate {

		unsigned int mu;
		float sigma2;

	} settings_samplerate;

	typedef struct settings_speedofsound {

		float mu;
		float sigma2;

	} settings_speedofsound;

	typedef struct settings_mic {

		float mu[3];
		float sigma2[9];
		float direction[3];
		float angle[2];

	} settings_mic;

	typedef struct settings_mics {

		settings_mic array[32];
		unsigned int N;

	} settings_mics;

	typedef struct settings_spatialfilter {

		float direction[3];
		float angle[2];

	} settings_spatialfilter;

	typedef struct settings_spatialfilters {

		settings_spatialfilter array[16];
		unsigned int N;

	} settings_spatialfilters;

	typedef struct settings_general {

		float epsilon;

		settings_size size;
		settings_samplerate samplerate;
		settings_speedofsound speedofsound;

		settings_mics mics;
		settings_spatialfilters spatialfilters;

		unsigned int nThetas;
		float gainMin;

	} settings_general;

	typedef struct settings_bf {

		unsigned int nSrcs;

		char mode[256];

	} settings_bf;

	typedef struct settings {

		settings_general general;
		settings_bf bf;

	} settings;

	settings * settings_construct(const char * file);

	void settings_destroy(settings * sets);

	void settings_printf(const settings * sets);

	config_setting_t * settings_lookup(const config_t * cfg, const char * s);

#endif