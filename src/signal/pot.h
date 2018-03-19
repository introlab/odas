#ifndef __ODAS_SIGNAL_POT
#define __ODAS_SIGNAL_POT

   /**
    * \file     pot.h
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

    typedef struct pots_obj {

        unsigned int nPots;
        float * array;

    } pots_obj;

    pots_obj * pots_construct_zero(const unsigned int nPots);

    pots_obj * pots_clone(const pots_obj * obj);

    void pots_copy(pots_obj * dest, const pots_obj * src);

    void pots_zero(pots_obj * obj);

    void pots_destroy(pots_obj * obj);

    void pots_printf(const pots_obj * obj);

#endif