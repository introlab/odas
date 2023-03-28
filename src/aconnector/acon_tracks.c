
    /**
    * \file     acon_tracks.c
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
    
    #include <aconnector/acon_tracks.h>

    acon_tracks_obj * acon_tracks_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config) {

        acon_tracks_obj * obj;
        unsigned int iOut;

        obj = (acon_tracks_obj *) malloc(sizeof(acon_tracks_obj));

        obj->in = amsg_tracks_construct(nMessages, msg_tracks_config);

        obj->outs = (amsg_tracks_obj **) malloc(sizeof(amsg_tracks_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_tracks_construct(nMessages, msg_tracks_config);
        }

        obj->con_tracks = con_tracks_construct(nOuts, msg_tracks_config);

        obj->thread = thread_construct(&acon_tracks_thread, (void *) obj);

        return obj;

    }

    void acon_tracks_destroy(acon_tracks_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_tracks->nOuts;

        thread_destroy(obj->thread);

        con_tracks_destroy(obj->con_tracks);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_tracks_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_tracks_destroy(obj->in);

        free((void *) obj);

    }

    void * acon_tracks_thread(void * ptr) {

        msg_tracks_obj * msg_tracks_in;
        msg_tracks_obj * msg_tracks_out;

        acon_tracks_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_tracks_obj *) ptr;

        nOuts = obj->con_tracks->nOuts;

        while(1) {

            msg_tracks_in = amsg_tracks_filled_pop(obj->in);
            msg_tracks_copy(obj->con_tracks->in, msg_tracks_in);
            amsg_tracks_empty_push(obj->in, msg_tracks_in);

            rtnValue = con_tracks_process(obj->con_tracks);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_tracks_out = amsg_tracks_empty_pop(obj->outs[iOut]);
                msg_tracks_copy(msg_tracks_out, obj->con_tracks->outs[iOut]);
                amsg_tracks_filled_push(obj->outs[iOut], msg_tracks_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
