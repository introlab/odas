#ifndef __ODAS_UTILS_INTERLEAVE
#define __ODAS_UTILS_INTERLEAVE

    /**
    * \file     interleave.h
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

	#include <string.h>

	void interleave_perchannel2interleave(char * dest, const char * src, const unsigned int nBytes, const unsigned int nChannels, const unsigned int nSamples);

	void interleave_interleave2perchannel(char * dest, const char * src, const unsigned int nBytes, const unsigned int nChannels, const unsigned int nSamples);

#endif