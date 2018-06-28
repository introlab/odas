#ifndef __ODAS_UTILS_INTERLEAVE
#define __ODAS_UTILS_INTERLEAVE

	#include <string.h>

	void interleave_perchannel2interleave(char * dest, const char * src, const unsigned int nBytes, const unsigned int nChannels, const unsigned int nSamples);

	void interleave_interleave2perchannel(char * dest, const char * src, const unsigned int nBytes, const unsigned int nChannels, const unsigned int nSamples);

#endif