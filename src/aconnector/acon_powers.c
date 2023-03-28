
    /**
    * \file     acon_powers.c
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
    
    #include <aconnector/acon_powers.h>

    acon_powers_obj * acon_powers_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_powers_cfg * msg_powers_config) {

        acon_powers_obj * obj;
        unsigned int iOut;

        obj = (acon_powers_obj *) malloc(sizeof(acon_powers_obj));

        obj->in = amsg_powers_construct(nMessages, msg_powers_config);

        obj->outs = (amsg_powers_obj **) malloc(sizeof(amsg_powers_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_powers_construct(nMessages, msg_powers_config);
        }

        obj->con_powers = con_powers_construct(nOuts, msg_powers_config);

        obj->thread = thread_construct(&acon_powers_thread, (void *) obj);

        return obj;

    }

    void acon_powers_destroy(acon_powers_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_powers->nOuts;

        thread_destroy(obj->thread);

        con_powers_destroy(obj->con_powers);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_powers_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_powers_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_powers_thread(void * ptr) {

        msg_powers_obj * msg_powers_in;
        msg_powers_obj * msg_powers_out;

        acon_powers_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_powers_obj *) ptr;

        nOuts = obj->con_powers->nOuts;

        while(1) {

            msg_powers_in = amsg_powers_filled_pop(obj->in);
            msg_powers_copy(obj->con_powers->in, msg_powers_in);
            amsg_powers_empty_push(obj->in, msg_powers_in);

            rtnValue = con_powers_process(obj->con_powers);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_powers_out = amsg_powers_empty_pop(obj->outs[iOut]);
                msg_powers_copy(msg_powers_out, obj->con_powers->outs[iOut]);
                amsg_powers_filled_push(obj->outs[iOut], msg_powers_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
