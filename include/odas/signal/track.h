#ifndef __ODAS_SIGNAL_TRACK
#define __ODAS_SIGNAL_TRACK

    /**
    * \file     track.h
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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

    typedef struct tracks_obj {

        unsigned int nTracks;
        unsigned long long * ids;
        char ** tags;
        float * array;
        float * activity;
        
    } tracks_obj;

    tracks_obj * tracks_construct_zero(const unsigned int nTracks);

    void tracks_destroy(tracks_obj * obj);

    tracks_obj * tracks_clone(const tracks_obj * obj);

    void tracks_copy(tracks_obj * dest, const tracks_obj * src);

    void tracks_zero(tracks_obj * obj);

    void tracks_printf(const tracks_obj * obj);

#endif