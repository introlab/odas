#ifndef __ODAS_SIGNAL_MIXTURE
#define __ODAS_SIGNAL_MIXTURE

   /**
    * \file     mixture.h
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

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../signal/assignation.h"
    #include "../init/combining.h"

    typedef struct mixture_obj {
       
        unsigned int nPots;
        unsigned int nTracks;
        unsigned int nTracksNewFalse;
        unsigned int nCombinations;

        assignations_obj * assignations;

        float * p_Ez_AICD;
        float * p_Eszs_phics;
        float * p_phics;
        float * p_Ez_phic;
        float * p_phic;
        float * p_phic_Ez;

    } mixture_obj;

    mixture_obj * mixture_construct_zero(const unsigned int nPots, const unsigned int nTracks);

    void mixture_destroy(mixture_obj * obj);

    void mixture_printf(const mixture_obj * obj);

#endif