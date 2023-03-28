
    /**
    * \file     acon_hops.c
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

    #include <aconnector/acon_hops.h>

    acon_hops_obj * acon_hops_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_hops_cfg * msg_hops_config) {

        acon_hops_obj * obj;
        unsigned int iOut;

        obj = (acon_hops_obj *) malloc(sizeof(acon_hops_obj));

        obj->in = amsg_hops_construct(nMessages, msg_hops_config);

        obj->outs = (amsg_hops_obj **) malloc(sizeof(amsg_hops_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_hops_construct(nMessages, msg_hops_config);
        }

        obj->con_hops = con_hops_construct(nOuts, msg_hops_config);

        obj->thread = thread_construct(&acon_hops_thread, (void *) obj);

        return obj;

    }

    void acon_hops_destroy(acon_hops_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_hops->nOuts;

        thread_destroy(obj->thread);

        con_hops_destroy(obj->con_hops);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_hops_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_hops_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_hops_thread(void * ptr) {

        msg_hops_obj * msg_hops_in;
        msg_hops_obj * msg_hops_out;

        acon_hops_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_hops_obj *) ptr;

        nOuts = obj->con_hops->nOuts;

        while(1) {

            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_hops_copy(obj->con_hops->in, msg_hops_in);
            amsg_hops_empty_push(obj->in, msg_hops_in);

            rtnValue = con_hops_process(obj->con_hops);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_hops_out = amsg_hops_empty_pop(obj->outs[iOut]);
                msg_hops_copy(msg_hops_out, obj->con_hops->outs[iOut]);
                amsg_hops_filled_push(obj->outs[iOut], msg_hops_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
