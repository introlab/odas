#ifndef __ODAS_GENERAL_SAMPLERATE
#define __ODAS_GENERAL_SAMPLERATE

   /**
    * \file     samplerate.h
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

    typedef struct samplerate_obj {

        unsigned int mu;
        float sigma2;

    } samplerate_obj;

    samplerate_obj * samplerate_construct_zero(void);

    samplerate_obj * samplerate_clone(const samplerate_obj * obj);

    void samplerate_destroy(samplerate_obj * obj);

    void samplerate_printf(const samplerate_obj * obj);

#endif