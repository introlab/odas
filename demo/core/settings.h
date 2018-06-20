#ifndef __ODAS_DEMO_CORE_SETTINGS
#define __ODAS_DEMO_CORE_SETTINGS

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <odas/odas.h>

	#define SETTINGS_NCHANNELS			32
	#define SETTINGS_NMICS 				32
	#define SETTINGS_NSCANS				4
	#define SETTINGS_NSPATIALFILTERS	16
	#define SETTINGS_NGAUSSIANS			16
	#define SETTINGS_NLEVELS			16
	#define SETTINGS_NTARGETS			4
	
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

		settings_mic array[SETTINGS_NMICS];
		unsigned int N;

	} settings_mics;

	typedef struct settings_spatialfilter {

		float direction[3];
		float angle[2];

	} settings_spatialfilter;

	typedef struct settings_spatialfilters {

		settings_spatialfilter array[SETTINGS_NSPATIALFILTERS];
		unsigned int N;

	} settings_spatialfilters;

	typedef struct settings_scan {

		unsigned int level;
		signed int delta;

	} settings_scan;

	typedef struct settings_scans {

		settings_scan array[SETTINGS_NSCANS];
		unsigned int N;

	} settings_scans;

	typedef struct settings_gaussian {

		float weight;
		float mu;
		float sigma2;

	} settings_gaussian;

	typedef struct settings_gmm {

		settings_gaussian array[SETTINGS_NGAUSSIANS];
		unsigned int N;

	} settings_gmm;

	typedef struct settings_sigmaR2 {

		float prob;
		float active;
		float target;

	} settings_sigmaR2;

	typedef struct settings_P {

		float pFalse;
		float pNew;
		float pTrack;

	} settings_P;

	typedef struct settings_level {

		float theta;
		unsigned int Ns[SETTINGS_NLEVELS];
		unsigned int N;

	} settings_level;

	typedef struct settings_levels {

		settings_level lNew;
		settings_level lProb;
		settings_level lInactive;

	} settings_levels;

	typedef struct settings_kalman {

		float sigmaQ;

	} settings_kalman;

	typedef struct settings_dynamics {

		float alpha;
		float beta;
		float ratio;

	} settings_dynamics;

	typedef struct settings_particle {

		unsigned int nParticles;

		settings_dynamics stationary;
		settings_dynamics velocity;
		settings_dynamics acceleration;

		float Nmin;

	} settings_particle;

	typedef struct settings_target {

		char tag[256];
		float x;
		float y;
		float z;

	} settings_target;

	typedef struct settings_targets {

		settings_target array[SETTINGS_NTARGETS];
		unsigned int N;

	} settings_targets;

	typedef struct settings_dds {

	} settings_dds;

	typedef struct settings_dgss {

		float mu;
		float lambda;

	} settings_dgss;

	typedef struct settings_dmvdr {

	} settings_dmvdr;

	typedef struct settings_stechniques {

		settings_dds dds;
		settings_dgss dgss;
		settings_dmvdr dmvdr;

	} settings_stechniques;

	typedef struct settings_ms {

		float alphaPmin;
		float eta;
		float alphaZ;
		float thetaWin;
		float alphaWin;
		float maxAbsenceProb;
		float Gmin;
		unsigned int winSizeLocal;
		unsigned int winSizeGlobal;
		unsigned int winSizeFrame;

	} settings_ms;

	typedef struct settings_ss {

		float Gmin;
		float Gmid;
		float Gslope;

	} settings_ss;

	typedef struct settings_ptechniques {

		settings_ms ms;
		settings_ss ss;

	} settings_ptechniques;	

	typedef struct settings_file {

		char path[1024];

	} settings_file;

	typedef struct settings_socket {

		unsigned int port;

	} settings_socket;

	typedef struct settings_soundcard {

		char device[256];

	} settings_soundcard;

	typedef struct settings_format {

		unsigned int fS;
		unsigned int hopSize;
		unsigned int nBits;

	} settings_format;

	typedef struct settings_interface {

		char type[256];

		settings_file file;
		settings_socket socket;
		settings_soundcard soundcard;

	} settings_interface;

	typedef struct settings_raw {

		settings_format format;		
		unsigned int nChannels;

		settings_interface input;
		settings_interface output;

	} settings_raw;

	typedef struct settings_mapping {

		unsigned int array[SETTINGS_NCHANNELS];
		unsigned int N;

	} settings_mapping;

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

	typedef struct settings_sne {

		unsigned int b;
		float alphaS;
		unsigned int L;
		float delta;
		float alphaD;

	} settings_sne;

	typedef struct settings_ssl {

		unsigned int nPots;
		unsigned int nMatches;
		float probMin;
		unsigned int nRefinedLevels;
		unsigned int interpRate;

		settings_scans scans;

		settings_interface output;

	} settings_ssl;

	typedef struct settings_sst {

		char mode[256];
		char add[256];

		settings_gmm active;
		settings_gmm inactive;
		settings_sigmaR2 sigmaR2;
		settings_P P;
		settings_levels levels;

		settings_particle particle;
		settings_kalman kalman;

		settings_targets targets;

		settings_interface input;
		settings_interface output;

	} settings_sst;

	typedef struct settings_separation {

		char mode[256];

		settings_stechniques techniques;

		settings_format format;
		settings_interface output;

	} settings_separation;

	typedef struct settings_postfiltering {

		char mode[256];

		settings_ptechniques techniques;

		settings_format format;
		settings_interface output;

	} settings_postfiltering;	

	typedef struct settings_sss {

		unsigned int offset;
		settings_separation separation;
		settings_postfiltering postfiltering;

	} settings_sss;

	typedef struct settings {

		json_tokens * tokens;

		settings_raw raw;
		settings_mapping mapping;
		settings_general general;
		settings_sne sne;
		settings_ssl ssl;
		settings_sst sst;
		settings_sss sss;

	} settings;

	settings * settings_construct(void);

	void settings_destroy(settings * sets);

	void settings_load(settings * sets, const char * file);

	void settings_printf(const settings * sets);

#endif