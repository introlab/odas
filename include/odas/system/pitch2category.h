#ifndef __ODAS_SYSTEM_PITCH2CATEGORY
#define __ODAS_SYSTEM_PITCH2CATEGORY

   /**
    * \file     pitch2category.h
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
    #include <math.h>

    #include <signal/category.h>
    #include <signal/pitch.h>
    #include <signal/track.h>
    
    typedef struct pitch2category_obj {

        unsigned int nSeps;

        float tauMin;
        float tauMax;
        float deltaTauMax;
        float alpha;
        float gamma;
        float phiMin;
        float r0;

        float * tausNow;
        float * tausPrev;
        float * deltaTausNow;
        float * deltaTausPrev;
        float * phisNow;
        float * phisPrev;
        float * vs;
        float * rs;
        char * categories;

    } pitch2category_obj;

    pitch2category_obj * pitch2category_construct_zero(const unsigned int nSeps, const float tauMin, const float tauMax, const float deltaTauMax, const float alpha, const float gamma, const float phiMin, const float r0);

    void pitch2category_destroy(pitch2category_obj * obj);

    void pitch2category_process(pitch2category_obj * obj, const pitches_obj * pitches, const tracks_obj * tracks, categories_obj * categories);

#endif
