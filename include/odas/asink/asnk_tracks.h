#ifndef __ODAS_ASINK_TRACKS
#define __ODAS_ASINK_TRACKS

    /**
    * \file     asink_tracks.h
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

    #include "../amessage/amsg_tracks.h"
    #include "../sink/snk_tracks.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_tracks_obj {

        snk_tracks_obj * snk_tracks;
        amsg_tracks_obj * in;
        thread_obj * thread;

    } asnk_tracks_obj;

    asnk_tracks_obj * asnk_tracks_construct(const snk_tracks_cfg * snk_tracks_config, const msg_tracks_cfg * msg_tracks_config);

    void asnk_tracks_destroy(asnk_tracks_obj * obj);

    void asnk_tracks_connect(asnk_tracks_obj * obj, amsg_tracks_obj * in);

    void asnk_tracks_disconnect(asnk_tracks_obj * obj);

    void * asnk_tracks_thread(void * ptr);

#endif