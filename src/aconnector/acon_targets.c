
    /**
    * \file     acon_targets.c
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
    
    #include <aconnector/acon_targets.h>

    acon_targets_obj * acon_targets_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_targets_cfg * msg_targets_config) {

        acon_targets_obj * obj;
        unsigned int iOut;

        obj = (acon_targets_obj *) malloc(sizeof(acon_targets_obj));

        obj->in = amsg_targets_construct(nMessages, msg_targets_config);

        obj->outs = (amsg_targets_obj **) malloc(sizeof(amsg_targets_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_targets_construct(nMessages, msg_targets_config);
        }

        obj->con_targets = con_targets_construct(nOuts, msg_targets_config);

        obj->thread = thread_construct(&acon_targets_thread, (void *) obj);

        return obj;

    }

    void acon_targets_destroy(acon_targets_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_targets->nOuts;

        thread_destroy(obj->thread);

        con_targets_destroy(obj->con_targets);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_targets_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_targets_destroy(obj->in);

        free((void *) obj);

    }

    void * acon_targets_thread(void * ptr) {

        msg_targets_obj * msg_targets_in;
        msg_targets_obj * msg_targets_out;

        acon_targets_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_targets_obj *) ptr;

        nOuts = obj->con_targets->nOuts;

        while(1) {

            msg_targets_in = amsg_targets_filled_pop(obj->in);
            msg_targets_copy(obj->con_targets->in, msg_targets_in);
            amsg_targets_empty_push(obj->in, msg_targets_in);

            rtnValue = con_targets_process(obj->con_targets);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_targets_out = amsg_targets_empty_pop(obj->outs[iOut]);
                msg_targets_copy(msg_targets_out, obj->con_targets->outs[iOut]);
                amsg_targets_filled_push(obj->outs[iOut], msg_targets_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
