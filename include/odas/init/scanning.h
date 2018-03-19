#ifndef __ODAS_INIT_SCANNING
#define __ODAS_INIT_SCANNING

   /**
    * \file     scanning.h
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

    #include <general/mic.h>
    #include <general/soundspeed.h>
    #include <general/spatialfilter.h>

    #include <signal/beampattern.h>
    #include <signal/scan.h>
    #include <signal/spatialgain.h>
    #include <signal/spatialindex.h>
    #include <signal/spatialmask.h>
    #include <signal/map.h>
    #include <signal/pair.h>
    #include <signal/tau.h>

    #include <init/delay.h>
    #include <init/directivity.h>
    #include <init/hit.h>
    #include <init/linking.h>
    #include <init/space.h>

    scans_obj * scanning_init_scans(const mics_obj * mics, const spatialfilter_obj * spatialfilter, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const unsigned int nMatches, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels, const unsigned int nThetas, const float gainMin, const unsigned int interpRate);

#endif
