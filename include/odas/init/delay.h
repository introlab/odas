#ifndef __ODAS_INIT_DELAY
#define __ODAS_INIT_DELAY

   /**
    * \file     delay.h
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

    #include <math.h>

    #include <general/mic.h>
    #include <general/soundspeed.h>

    #include <signal/delta.h>
    #include <signal/point.h>
    #include <signal/tdoa.h>
    #include <signal/tau.h>

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize, const unsigned int interpRate);

    //tdoas_obj * delay_tdoas_minmax(const tdoas_obj * tdoas, const deltas_obj * deltas);

    //void delay_tdoas_allminmax(tdoas_obj * tdoas, const tdoas_obj * minmax);

    taus_obj * delay_taus(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize, const unsigned int interpRate);

#endif

    
