
    /**
    * \file     asnk_pots.c
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
    
    #include <asink/asnk_pots.h>

    asnk_pots_obj * asnk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config) {

        asnk_pots_obj * obj;

        obj = (asnk_pots_obj *) malloc(sizeof(asnk_pots_obj));

        obj->snk_pots = snk_pots_construct(snk_pots_config, msg_pots_config);
        obj->in = (amsg_pots_obj *) NULL;

        obj->thread = thread_construct(&asnk_pots_thread, (void *) obj);

        return obj;

    }

    void asnk_pots_destroy(asnk_pots_obj * obj) {

        snk_pots_destroy(obj->snk_pots);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_pots_connect(asnk_pots_obj * obj, amsg_pots_obj * in) {

        obj->in = in;

    }

    void asnk_pots_disconnect(asnk_pots_obj * obj) {

        obj->in = (amsg_pots_obj *) NULL;

    }

    void * asnk_pots_thread(void * ptr) {

        asnk_pots_obj * obj;
        msg_pots_obj * msg_pots_in;
        int rtnValue;

        obj = (asnk_pots_obj *) ptr;

        // Open the sink
        snk_pots_open(obj->snk_pots);

        while(1) {

            // Pop a message, process, and push back
            msg_pots_in = amsg_pots_filled_pop(obj->in);
            snk_pots_connect(obj->snk_pots, msg_pots_in);
            rtnValue = snk_pots_process(obj->snk_pots);
            snk_pots_disconnect(obj->snk_pots);
            amsg_pots_empty_push(obj->in, msg_pots_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_pots_close(obj->snk_pots);

    }
