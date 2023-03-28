
    /**
    * \file     amod_stft.c
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

    #include <amodule/amod_stft.h>

    amod_stft_obj * amod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config) {

        amod_stft_obj * obj;

        obj = (amod_stft_obj *) malloc(sizeof(amod_stft_obj));

        obj->mod_stft = mod_stft_construct(mod_stft_config, msg_hops_config, msg_spectra_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

        obj->thread = thread_construct(&amod_stft_thread, (void *) obj);

        mod_stft_disable(obj->mod_stft);

        return obj;

    }

    void amod_stft_destroy(amod_stft_obj * obj) {

        mod_stft_destroy(obj->mod_stft);
        thread_destroy(obj->thread);

        free((void *) obj);           

    }

    void amod_stft_connect(amod_stft_obj * obj, amsg_hops_obj * in, amsg_spectra_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_stft_disconnect(amod_stft_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

    }

    void amod_stft_enable(amod_stft_obj * obj) {

        mod_stft_enable(obj->mod_stft);

    }

    void amod_stft_disable(amod_stft_obj * obj) {

        mod_stft_disable(obj->mod_stft);

    }

    void * amod_stft_thread(void * ptr) {

        amod_stft_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_spectra_obj * msg_spectra_out;
        int rtnValue;

        obj = (amod_stft_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_spectra_out = amsg_spectra_empty_pop(obj->out);
            mod_stft_connect(obj->mod_stft, msg_hops_in, msg_spectra_out);
            rtnValue = mod_stft_process(obj->mod_stft);
            mod_stft_disconnect(obj->mod_stft);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_spectra_filled_push(obj->out, msg_spectra_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
