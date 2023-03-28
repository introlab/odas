
    /**
    * \file     amod_ssl.c
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
    
    #include <amodule/amod_ssl.h>

    amod_ssl_obj * amod_ssl_construct(const mod_ssl_cfg * mod_ssl_config, const msg_spectra_cfg * msg_spectra_config, const msg_pots_cfg * msg_pots_config) {

        amod_ssl_obj * obj;

        obj = (amod_ssl_obj *) malloc(sizeof(amod_ssl_obj));

        obj->mod_ssl = mod_ssl_construct(mod_ssl_config, msg_spectra_config, msg_pots_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_pots_obj *) NULL;

        obj->thread = thread_construct(&amod_ssl_thread, (void *) obj);

        mod_ssl_disable(obj->mod_ssl);

        return obj;

    }

    void amod_ssl_destroy(amod_ssl_obj * obj) {

        mod_ssl_destroy(obj->mod_ssl);
        thread_destroy(obj->thread);

        free((void *) obj); 

    }

    void amod_ssl_connect(amod_ssl_obj * obj, amsg_spectra_obj * in, amsg_pots_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_ssl_disconnect(amod_ssl_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_pots_obj *) NULL;

    }

    void amod_ssl_enable(amod_ssl_obj * obj) {

        mod_ssl_enable(obj->mod_ssl);

    }

    void amod_ssl_disable(amod_ssl_obj * obj) {

        mod_ssl_disable(obj->mod_ssl);

    }

    void * amod_ssl_thread(void * ptr) {

        amod_ssl_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_pots_obj * msg_pots_out;
        int rtnValue;

        obj = (amod_ssl_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_pots_out = amsg_pots_empty_pop(obj->out);
            mod_ssl_connect(obj->mod_ssl, msg_spectra_in, msg_pots_out);
            rtnValue = mod_ssl_process(obj->mod_ssl);
            mod_ssl_disconnect(obj->mod_ssl);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_pots_filled_push(obj->out, msg_pots_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }


        }

    }
