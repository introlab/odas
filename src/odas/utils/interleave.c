
	#include <utils/interleave.h>

	void interleave_perchannel2interleave(char * dest, const char * src, const unsigned int nBytes, const unsigned int nChannels, const unsigned int nSamples) {

		unsigned int iChannel;
		unsigned int iSample;
		unsigned int iByteSrc;
		unsigned int iByteDst;

		for (iChannel = 0; iChannel < nChannels; iChannel++) {

			for (iSample = 0; iSample < nSamples; iSample++) {

				iByteSrc = iChannel * nSamples * nBytes + iSample * nBytes;
				iByteDst = iSample * nChannels * nBytes + iChannel * nBytes;

				memcpy(&(dest[iByteDst]), &(src[iByteSrc]), nBytes * sizeof(char));


			}

		}

	}

	void interleave_interleave2perchannel(char * dest, const char * src, const unsigned int nBytes, const unsigned int nChannels, const unsigned int nSamples) {

		unsigned int iChannel;
		unsigned int iSample;
		unsigned int iByteSrc;
		unsigned int iByteDst;

		for (iSample = 0; iSample < nSamples; iSample++) {

			for (iChannel = 0; iChannel < nChannels; iChannel++) {		

				iByteSrc = iSample * nChannels * nBytes + iChannel * nBytes;
				iByteDst = iChannel * nSamples * nBytes + iSample * nBytes;

				memcpy(&(dest[iByteDst]), &(src[iByteSrc]), nBytes * sizeof(char));

			}

		}

	}
