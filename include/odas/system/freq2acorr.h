#ifndef __ODAS_SYSTEM_FREQ2ACORR
#define __ODAS_SYSTEM_FREQ2ACORR

   /**
    * \file     freq2acorr.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
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

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include <signal/acorr.h>
    #include <signal/freq.h>
    #include <utils/fft.h>

    typedef struct freq2acorr_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        unsigned int frameSize;

        float * arrayIn;
        float * arrayOut;

        fft_obj * fft;

    } freq2acorr_obj;

    freq2acorr_obj * freq2acorr_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    void freq2acorr_destroy(freq2acorr_obj * obj);

    void freq2acorr_process(freq2acorr_obj * obj, const freqs_obj * freqs, acorrs_obj * acorrs);

#endif
