#ifndef __ODAS_ACONNECTOR_TRACKS
#define __ODAS_ACONNECTOR_TRACKS

    /**
    * \file     acon_tracks.h
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

    #include "../connector/con_tracks.h"
    #include "../amessage/amsg_tracks.h"
    #include "../message/msg_tracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_tracks_obj {

        amsg_tracks_obj * in;
        amsg_tracks_obj ** outs;
        con_tracks_obj * con_tracks;
        thread_obj * thread;

    } acon_tracks_obj;

    acon_tracks_obj * acon_tracks_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config);

    void acon_tracks_destroy(acon_tracks_obj * obj);

    void * acon_tracks_thread(void * ptr);

#endif