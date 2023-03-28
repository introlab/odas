
    /**
    * \file     amod_istft.c
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
    
    #include <amodule/amod_istft.h>

    amod_istft_obj * amod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config) {

        amod_istft_obj * obj;

        obj = (amod_istft_obj *) malloc(sizeof(amod_istft_obj));

        obj->mod_istft = mod_istft_construct(mod_istft_config, msg_spectra_config, msg_hops_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;        

        obj->thread = thread_construct(&amod_istft_thread, (void *) obj);

        mod_istft_disable(obj->mod_istft);

        return obj;

    }

    void amod_istft_destroy(amod_istft_obj * obj) {

        mod_istft_destroy(obj->mod_istft);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_istft_connect(amod_istft_obj * obj, amsg_spectra_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_istft_disconnect(amod_istft_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

    }

    void amod_istft_enable(amod_istft_obj * obj) {

        mod_istft_enable(obj->mod_istft);

    }

    void amod_istft_disable(amod_istft_obj * obj) {

        mod_istft_disable(obj->mod_istft);

    }

    void * amod_istft_thread(void * ptr) {

        amod_istft_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (amod_istft_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_hops_out = amsg_hops_empty_pop(obj->out);
            mod_istft_connect(obj->mod_istft, msg_spectra_in, msg_hops_out);
            rtnValue = mod_istft_process(obj->mod_istft);
            mod_istft_disconnect(obj->mod_istft);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_hops_filled_push(obj->out, msg_hops_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
