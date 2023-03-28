
    /**
    * \file     acon_spectra.c
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
    
    #include <aconnector/acon_spectra.h>

    acon_spectra_obj * acon_spectra_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_spectra_cfg * msg_spectra_config) {

        acon_spectra_obj * obj;
        unsigned int iOut;

        obj = (acon_spectra_obj *) malloc(sizeof(acon_spectra_obj));

        obj->in = amsg_spectra_construct(nMessages, msg_spectra_config);

        obj->outs = (amsg_spectra_obj **) malloc(sizeof(amsg_spectra_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_spectra_construct(nMessages, msg_spectra_config);
        }

        obj->con_spectra = con_spectra_construct(nOuts, msg_spectra_config);

        obj->thread = thread_construct(&acon_spectra_thread, (void *) obj);

        return obj;

    }

    void acon_spectra_destroy(acon_spectra_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_spectra->nOuts;

        thread_destroy(obj->thread);

        con_spectra_destroy(obj->con_spectra);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_spectra_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_spectra_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_spectra_thread(void * ptr) {

        msg_spectra_obj * msg_spectra_in;
        msg_spectra_obj * msg_spectra_out;

        acon_spectra_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_spectra_obj *) ptr;

        nOuts = obj->con_spectra->nOuts;

        while(1) {

            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_spectra_copy(obj->con_spectra->in, msg_spectra_in);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);

            rtnValue = con_spectra_process(obj->con_spectra);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_spectra_out = amsg_spectra_empty_pop(obj->outs[iOut]);
                msg_spectra_copy(msg_spectra_out, obj->con_spectra->outs[iOut]);
                amsg_spectra_filled_push(obj->outs[iOut], msg_spectra_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
