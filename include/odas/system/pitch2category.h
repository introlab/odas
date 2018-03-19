#ifndef __ODAS_SYSTEM_PITCH2CATEGORY
#define __ODAS_SYSTEM_PITCH2CATEGORY

   /**
    * \file     pitch2category.h
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
