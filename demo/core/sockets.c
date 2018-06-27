	
	#include "sockets.h"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <odas/odas.h>

	sockets * sockets_construct(void) {

		sockets * scks;

		scks = (sockets *) malloc(sizeof(sockets));

		scks->raw = 0;
		scks->targets = 0;

		scks->pots = 0;
		scks->tracks = 0;
		scks->seps = 0;
		scks->pfs = 0;
		scks->iseps = 0;
		scks->ipfs = 0;

		return scks;

	}

	void sockets_destroy(sockets * scks) {

		free((void *) scks);

	}

	void sockets_load(sockets * scks, const char * file) {

		json_tokens * tokens;
		char * line;
		char * string;
		FILE * fp;
		char * rtnPtr;

		unsigned int nTokens = 256;
		unsigned int nBytesPerLine = 1024;
		unsigned int nBytesPerString = 4096;

		int parseRtn;

		int token_root_O;

		int token_root_sockets_V;
		int token_root_sockets_O;

		int token_root_sockets_raw_V;
		int token_root_sockets_raw_N;
		int token_root_sockets_targets_V;
		int token_root_sockets_targets_N;
		int token_root_sockets_pots_V;
		int token_root_sockets_pots_N;
		int token_root_sockets_tracks_V;
		int token_root_sockets_tracks_N;
		int token_root_sockets_seps_V;
		int token_root_sockets_seps_N;
		int token_root_sockets_pfs_V;
		int token_root_sockets_pfs_N;
		int token_root_sockets_iseps_V;
		int token_root_sockets_iseps_N;
		int token_root_sockets_ipfs_V;
		int token_root_sockets_ipfs_N;

		// Allocate	

		tokens = json_tokens_construct(nTokens);
		line = (char *) malloc(sizeof(char) * nBytesPerLine);
		string = (char *) malloc(sizeof(char) * nBytesPerString);

		// Load file in a string

		fp = fopen(file, "r");
		string[0] = 0x00;
		if (fp == NULL) { printf("Cannot open file %s\n", file); exit(EXIT_FAILURE); }
		while(feof(fp)==0) {
			line[0] = 0x00;
			rtnPtr = fgets(line, nBytesPerLine, fp);
			if ((strlen(line) + strlen(string)) > nBytesPerString) { printf("Buffer overflow while loading JSON\n"); exit(EXIT_FAILURE); }
			strcat(string, line);
		}
		fclose(fp);

		// Parse
		
		json_tokens_clear(tokens);
		parseRtn = json_tokens_parse(tokens, string);
		if (parseRtn == -1) { printf("JSON file has invalid format\n"); exit(EXIT_FAILURE); }

		token_root_O = json_tokens_getFromValue(tokens, string, -1); sockets_validate(token_root_O);

		token_root_sockets_V = json_tokens_getFromObject(tokens, string, token_root_O, "sockets"); sockets_validate(token_root_sockets_V);
		token_root_sockets_O = json_tokens_getFromValue(tokens, string, token_root_sockets_V); sockets_validate(token_root_sockets_O);

		token_root_sockets_raw_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "raw"); sockets_validate(token_root_sockets_raw_V);
		token_root_sockets_raw_N = json_tokens_getFromValue(tokens, string, token_root_sockets_raw_V); sockets_validate(token_root_sockets_raw_N);
		token_root_sockets_targets_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "targets"); sockets_validate(token_root_sockets_targets_V);
		token_root_sockets_targets_N = json_tokens_getFromValue(tokens, string, token_root_sockets_targets_V); sockets_validate(token_root_sockets_targets_N);
		token_root_sockets_pots_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "pots"); sockets_validate(token_root_sockets_pots_V);
		token_root_sockets_pots_N = json_tokens_getFromValue(tokens, string, token_root_sockets_pots_V); sockets_validate(token_root_sockets_pots_N);
		token_root_sockets_tracks_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "tracks"); sockets_validate(token_root_sockets_tracks_V);
		token_root_sockets_tracks_N = json_tokens_getFromValue(tokens, string, token_root_sockets_tracks_V); sockets_validate(token_root_sockets_tracks_N);
		token_root_sockets_seps_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "seps"); sockets_validate(token_root_sockets_seps_V);
		token_root_sockets_seps_N = json_tokens_getFromValue(tokens, string, token_root_sockets_seps_V); sockets_validate(token_root_sockets_seps_N);
		token_root_sockets_pfs_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "pfs"); sockets_validate(token_root_sockets_pfs_V);
		token_root_sockets_pfs_N = json_tokens_getFromValue(tokens, string, token_root_sockets_pfs_V); sockets_validate(token_root_sockets_pfs_N);
		token_root_sockets_iseps_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "iseps"); sockets_validate(token_root_sockets_iseps_V);
		token_root_sockets_iseps_N = json_tokens_getFromValue(tokens, string, token_root_sockets_iseps_V); sockets_validate(token_root_sockets_iseps_N);
		token_root_sockets_ipfs_V = json_tokens_getFromObject(tokens, string, token_root_sockets_O, "ipfs"); sockets_validate(token_root_sockets_ipfs_V);
		token_root_sockets_ipfs_N = json_tokens_getFromValue(tokens, string, token_root_sockets_ipfs_V); sockets_validate(token_root_sockets_ipfs_N);

		// Access each token

		json_tokens_extractInt(tokens, string, token_root_sockets_raw_N, &(scks->raw));
		json_tokens_extractInt(tokens, string, token_root_sockets_targets_N, &(scks->targets));
		json_tokens_extractInt(tokens, string, token_root_sockets_pots_N, &(scks->pots));
		json_tokens_extractInt(tokens, string, token_root_sockets_tracks_N, &(scks->tracks));
		json_tokens_extractInt(tokens, string, token_root_sockets_seps_N, &(scks->seps));
		json_tokens_extractInt(tokens, string, token_root_sockets_pfs_N, &(scks->pfs));
		json_tokens_extractInt(tokens, string, token_root_sockets_iseps_N, &(scks->iseps));
		json_tokens_extractInt(tokens, string, token_root_sockets_ipfs_N, &(scks->ipfs));

		// Free

		free((void *) line);
		free((void *) string);
		json_tokens_destroy(tokens);

	}

	void sockets_printf(const sockets * scks) {

		printf("sockets.raw = %u\n", scks->raw);
		printf("sockets.targets = %u\n", scks->targets);
		printf("sockets.pots = %u\n", scks->pots);
		printf("sockets.tracks = %u\n", scks->tracks);
		printf("sockets.seps = %u\n", scks->seps);
		printf("sockets.pfs = %u\n", scks->pfs);
		printf("sockets.iseps = %u\n", scks->iseps);
		printf("sockets.ipfs = %u\n", scks->ipfs);

	}

	void sockets_validate(int token) {

		if (token == -1) {

			printf("Error parsing JSON\n");
			exit(EXIT_FAILURE);

		}

	}