
   /**
    * \file     combining.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
