#ifndef __ODAS_SYSTEM_TRACK2GAIN
#define __ODAS_SYSTEM_TRACK2GAIN

   /**
    * \file     track2gain.h
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

    #include <signal/beampattern.h>
    #include <signal/track.h>
    #include <signal/gain.h>

    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    typedef struct track2gain_obj {

        unsigned int nSeps;
        unsigned int nChannels;
        float * directions;
        float * direction;

    } track2gain_obj;

    track2gain_obj * track2gain_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const float * directions);

    void track2gain_destroy(track2gain_obj * obj);

    void track2gain_process(track2gain_obj * obj, const beampatterns_obj * beampatterns_mics, const tracks_obj * tracks, gains_obj * gains);


#endif
