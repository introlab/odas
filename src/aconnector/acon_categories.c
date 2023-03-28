
    /**
    * \file     acon_categories.c
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

    #include <aconnector/acon_categories.h>

    acon_categories_obj * acon_categories_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_categories_cfg * msg_categories_config) {

        acon_categories_obj * obj;
        unsigned int iOut;

        obj = (acon_categories_obj *) malloc(sizeof(acon_categories_obj));

        obj->in = amsg_categories_construct(nMessages, msg_categories_config);

        obj->outs = (amsg_categories_obj **) malloc(sizeof(amsg_categories_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_categories_construct(nMessages, msg_categories_config);
        }

        obj->con_categories = con_categories_construct(nOuts, msg_categories_config);

        obj->thread = thread_construct(&acon_categories_thread, (void *) obj);

        return obj;

    }

    void acon_categories_destroy(acon_categories_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_categories->nOuts;

        thread_destroy(obj->thread);

        con_categories_destroy(obj->con_categories);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_categories_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_categories_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_categories_thread(void * ptr) {

        msg_categories_obj * msg_categories_in;
        msg_categories_obj * msg_categories_out;

        acon_categories_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_categories_obj *) ptr;

        nOuts = obj->con_categories->nOuts;

        while(1) {

            msg_categories_in = amsg_categories_filled_pop(obj->in);
            msg_categories_copy(obj->con_categories->in, msg_categories_in);
            amsg_categories_empty_push(obj->in, msg_categories_in);

            rtnValue = con_categories_process(obj->con_categories);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_categories_out = amsg_categories_empty_pop(obj->outs[iOut]);
                msg_categories_copy(msg_categories_out, obj->con_categories->outs[iOut]);
                amsg_categories_filled_push(obj->outs[iOut], msg_categories_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
