
    /**
    * \file     acon_pots.c
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
    
    #include <aconnector/acon_pots.h>

    acon_pots_obj * acon_pots_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_pots_cfg * msg_pots_config) {

        acon_pots_obj * obj;
        unsigned int iOut;

        obj = (acon_pots_obj *) malloc(sizeof(acon_pots_obj));

        obj->in = amsg_pots_construct(nMessages, msg_pots_config);

        obj->outs = (amsg_pots_obj **) malloc(sizeof(amsg_pots_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_pots_construct(nMessages, msg_pots_config);
        }

        obj->con_pots = con_pots_construct(nOuts, msg_pots_config);

        obj->thread = thread_construct(&acon_pots_thread, (void *) obj);

        return obj;

    }

    void acon_pots_destroy(acon_pots_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_pots->nOuts;

        thread_destroy(obj->thread);

        con_pots_destroy(obj->con_pots);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_pots_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_pots_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_pots_thread(void * ptr) {

        msg_pots_obj * msg_pots_in;
        msg_pots_obj * msg_pots_out;

        acon_pots_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_pots_obj *) ptr;

        nOuts = obj->con_pots->nOuts;

        while(1) {

            msg_pots_in = amsg_pots_filled_pop(obj->in);
            msg_pots_copy(obj->con_pots->in, msg_pots_in);
            amsg_pots_empty_push(obj->in, msg_pots_in);

            rtnValue = con_pots_process(obj->con_pots);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_pots_out = amsg_pots_empty_pop(obj->outs[iOut]);
                msg_pots_copy(msg_pots_out, obj->con_pots->outs[iOut]);
                amsg_pots_filled_push(obj->outs[iOut], msg_pots_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
