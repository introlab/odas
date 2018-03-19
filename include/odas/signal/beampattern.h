#ifndef __ODAS_SIGNAL_BEAMPATTERN
#define __ODAS_SIGNAL_BEAMPATTERN

   /**
    * \file     beampattern.h
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
    #include <stdio.h>
    #include <string.h>

    typedef struct beampatterns_obj {

        unsigned int nChannels;
        unsigned int nThetas;

        float * minThetas;
        float * maxThetas;
        float * deltaThetas;
                        
        float * gains;

    } beampatterns_obj;

    beampatterns_obj * beampatterns_construct_zero(const unsigned int nChannels, const unsigned int nThetas);

    void beampatterns_destroy(beampatterns_obj * obj);

    void beampatterns_printf(const beampatterns_obj * obj);

#endif