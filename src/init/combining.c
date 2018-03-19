
   /**
    * \file     combining.c
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

    #include <init/combining.h>

    assignations_obj * combining_generate(const unsigned int nPots, const unsigned int nTracks) {

        assignations_obj * obj;
        
        unsigned int nCombinations;
        unsigned int iCombination;
        unsigned int iPot;
        
        signed int carry;
        signed int digit;

        nCombinations = 1;

        for (iPot = 0; iPot < nPots; iPot++) {

            nCombinations *= (2+nTracks);

        }

        obj = assignations_construct_zero(nCombinations, nPots);      

        for (iPot = 0; iPot < nPots; iPot++) {

            obj->array[iPot] = -2;

        }

        for (iCombination = 1; iCombination < nCombinations; iCombination++) {

            carry = 1;

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                digit = obj->array[(iCombination-1) * obj->nPots + obj->nPots - iPot - 1];

                digit += carry;

                if (digit == nTracks) {

                    digit = -2;
                    carry = 1;

                }
                else {

                    carry = 0;

                }

                obj->array[iCombination * obj->nPots + obj->nPots - iPot - 1] = digit;

            }

        }

        return obj;

    }
