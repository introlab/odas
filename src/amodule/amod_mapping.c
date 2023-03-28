
    /**
    * \file     amod_mapping.c
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
    
    #include <amodule/amod_mapping.h>

    amod_mapping_obj * amod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config) {

        amod_mapping_obj * obj;

        obj = (amod_mapping_obj *) malloc(sizeof(amod_mapping_obj));

        obj->mod_mapping = mod_mapping_construct(mod_mapping_config, msg_hops_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

        obj->thread = thread_construct(&amod_mapping_thread, (void *) obj);

        mod_mapping_disable(obj->mod_mapping);

        return obj;

    }

    void amod_mapping_destroy(amod_mapping_obj * obj) {

        mod_mapping_destroy(obj->mod_mapping);
        thread_destroy(obj->thread);

        free((void *) obj);        

    }

    void amod_mapping_connect(amod_mapping_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_mapping_disconnect(amod_mapping_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

    }

    void amod_mapping_enable(amod_mapping_obj * obj) {

        mod_mapping_enable(obj->mod_mapping);

    }

    void amod_mapping_disable(amod_mapping_obj * obj) {

        mod_mapping_disable(obj->mod_mapping);

    }

    void * amod_mapping_thread(void * ptr) {

        amod_mapping_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (amod_mapping_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_hops_out = amsg_hops_empty_pop(obj->out);
            mod_mapping_connect(obj->mod_mapping, msg_hops_in, msg_hops_out);
            rtnValue = mod_mapping_process(obj->mod_mapping);
            mod_mapping_disconnect(obj->mod_mapping);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_hops_filled_push(obj->out, msg_hops_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
