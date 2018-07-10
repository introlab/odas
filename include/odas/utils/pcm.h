#ifndef __ODAS_UTILS_PCM
#define __ODAS_UTILS_PCM

    /**
    * \file     pcm.h
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

    #include <math.h>
    #include <limits.h>
    #include <stdlib.h>
    #include <string.h>

    void pcm_SXle2normalized(float * normalized, const char * SXle, const unsigned int nBytes, const unsigned int nSamples);

    void pcm_normalized2SXle(char * SXle, const float * normalized, const unsigned int nBytes, const unsigned int nSamples);

#endif