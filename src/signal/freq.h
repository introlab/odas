#ifndef __ODAS_SIGNAL_FREQ
#define __ODAS_SIGNAL_FREQ

   /**
    * \file     freq.h
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

    typedef struct freqs_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        float ** array;

    } freqs_obj;

    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    freqs_obj * freqs_clone(const freqs_obj * obj);

    void freqs_copy(freqs_obj * dest, const freqs_obj * src);

    void freqs_zero(freqs_obj * obj);

    void freqs_destroy(freqs_obj * obj);

    void freqs_printf(const freqs_obj * obj);

#endif