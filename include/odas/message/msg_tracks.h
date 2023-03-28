#ifndef __ODAS_MESSAGE_TRACKS
#define __ODAS_MESSAGE_TRACKS

   /**
    * \file     msg_tracks.h
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
    #include "../signal/track.h"

    typedef struct msg_tracks_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        tracks_obj * tracks;

    } msg_tracks_obj;

    typedef struct msg_tracks_cfg {

        unsigned int nTracks;
        unsigned int fS;

    } msg_tracks_cfg;

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg);

    void msg_tracks_destroy(msg_tracks_obj * obj);

    void msg_tracks_copy(msg_tracks_obj * dest, const msg_tracks_obj * src);

    void msg_tracks_zero(msg_tracks_obj * obj);

    unsigned int msg_tracks_isZero(const msg_tracks_obj * obj);

    msg_tracks_cfg * msg_tracks_cfg_construct(void);

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg);

    void msg_tracks_cfg_printf(const msg_tracks_cfg * msg_tracks_config);

#endif