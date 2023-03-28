
    /**
    * \file     asnk_spectra.c
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
    
    #include <asink/asnk_spectra.h>

    asnk_spectra_obj * asnk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config) {

        asnk_spectra_obj * obj;

        obj = (asnk_spectra_obj *) malloc(sizeof(asnk_spectra_obj));

        obj->snk_spectra = snk_spectra_construct(snk_spectra_config, msg_spectra_config);
        obj->in = (amsg_spectra_obj *) NULL;

        obj->thread = thread_construct(&asnk_spectra_thread, (void *) obj);

        return obj;

    }

    void asnk_spectra_destroy(asnk_spectra_obj * obj) {

        snk_spectra_destroy(obj->snk_spectra);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_spectra_connect(asnk_spectra_obj * obj, amsg_spectra_obj * in) {

        obj->in = in;

    }

    void asnk_spectra_disconnect(asnk_spectra_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;

    }

    void * asnk_spectra_thread(void * ptr) {

        asnk_spectra_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        int rtnValue;

        obj = (asnk_spectra_obj *) ptr;

        // Open the sink
        snk_spectra_open(obj->snk_spectra);

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            snk_spectra_connect(obj->snk_spectra, msg_spectra_in);
            rtnValue = snk_spectra_process(obj->snk_spectra);
            snk_spectra_disconnect(obj->snk_spectra);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_spectra_close(obj->snk_spectra);

    }
