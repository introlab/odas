#ifndef __ODAS_GENERAL_MIC
#define __ODAS_GENERAL_MIC

   /**
    * \file     mic.h
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

    typedef struct mics_obj {

        unsigned int nChannels;
        unsigned int nPairs;
        float * mu;
        float * sigma2;
        float * direction;
        float * thetaAllPass;
        float * thetaNoPass;

    } mics_obj;

    mics_obj * mics_construct_zero(const unsigned int nChannels);

    mics_obj * mics_clone(const mics_obj * obj);

    void mics_destroy(mics_obj * obj);

    void mics_printf(const mics_obj * obj);

#endif