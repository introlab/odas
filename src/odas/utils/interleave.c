
    /**
    * \file     interleave.c
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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
