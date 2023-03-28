
    /**
    * \file     asnk_categories.c
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

    #include <asink/asnk_categories.h>

    asnk_categories_obj * asnk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config) {

        asnk_categories_obj * obj;

        obj = (asnk_categories_obj *) malloc(sizeof(asnk_categories_obj));

        obj->snk_categories = snk_categories_construct(snk_categories_config, msg_categories_config);
        obj->in = (amsg_categories_obj *) NULL;

        obj->thread = thread_construct(&asnk_categories_thread, (void *) obj);

        return obj;

    }

    void asnk_categories_destroy(asnk_categories_obj * obj) {

        snk_categories_destroy(obj->snk_categories);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_categories_connect(asnk_categories_obj * obj, amsg_categories_obj * in) {

        obj->in = in;

    }

    void asnk_categories_disconnect(asnk_categories_obj * obj) {

        obj->in = (amsg_categories_obj *) NULL;

    }

    void * asnk_categories_thread(void * ptr) {

        asnk_categories_obj * obj;
        msg_categories_obj * msg_categories_in;
        int rtnValue;

        obj = (asnk_categories_obj *) ptr;

        // Open the sink
        snk_categories_open(obj->snk_categories);

        while(1) {

            // Pop a message, process, and push back
            msg_categories_in = amsg_categories_filled_pop(obj->in);
            snk_categories_connect(obj->snk_categories, msg_categories_in);
            rtnValue = snk_categories_process(obj->snk_categories);
            snk_categories_disconnect(obj->snk_categories);
            amsg_categories_empty_push(obj->in, msg_categories_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_categories_close(obj->snk_categories);

    }
