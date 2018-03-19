#ifndef __ODAS_SYSTEM_DEMIXING2FREQ
#define __ODAS_SYSTEM_DEMIXING2FREQ

   /**
    * \file     demixing2freq.h
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
    #include <math.h>

    #include <signal/demixing.h>
    #include <signal/freq.h>
    #include <signal/mask.h>
    #include <signal/track.h>
    
    typedef struct demixing2freq_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        unsigned int halfFrameSize;

    } demixing2freq_obj;    

    demixing2freq_obj * demixing2freq_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize);

    void demixing2freq_destroy(demixing2freq_obj * obj);

    void demixing2freq_process(demixing2freq_obj * obj, const tracks_obj * tracks, const demixings_obj * demixings, const masks_obj * masks, const freqs_obj * freqsChannel, freqs_obj * freqsSeparated);

#endif
