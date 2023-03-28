
    /**
    * \file     amod_noise.c
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
    
    #include <amodule/amod_noise.h>

    amod_noise_obj * amod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config) {

        amod_noise_obj * obj;

        obj = (amod_noise_obj *) malloc(sizeof(amod_noise_obj));

        obj->mod_noise = mod_noise_construct(mod_noise_config, msg_spectra_config, msg_powers_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_powers_obj *) NULL;

        obj->thread = thread_construct(&amod_noise_thread, (void *) obj);

        mod_noise_disable(obj->mod_noise);

        return obj;

    }

    void amod_noise_destroy(amod_noise_obj * obj) {

        mod_noise_destroy(obj->mod_noise);
        thread_destroy(obj->thread);

        free((void *) obj);     

    }

    void amod_noise_connect(amod_noise_obj * obj, amsg_spectra_obj * in, amsg_powers_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_noise_disconnect(amod_noise_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_powers_obj *) NULL;

    }

    void amod_noise_enable(amod_noise_obj * obj) {

        mod_noise_enable(obj->mod_noise);

    }

    void amod_noise_disable(amod_noise_obj * obj) {

        mod_noise_disable(obj->mod_noise);

    }

    void * amod_noise_thread(void * ptr) {

        amod_noise_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_powers_obj * msg_powers_out;
        int rtnValue;

        obj = (amod_noise_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_powers_out = amsg_powers_empty_pop(obj->out);
            mod_noise_connect(obj->mod_noise, msg_spectra_in, msg_powers_out);
            rtnValue = mod_noise_process(obj->mod_noise);
            mod_noise_disconnect(obj->mod_noise);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_powers_filled_push(obj->out, msg_powers_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
