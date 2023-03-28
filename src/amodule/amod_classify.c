
    /**
    * \file     amod_classify.c
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
    
    #include <amodule/amod_classify.h>

    amod_classify_obj * amod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config, const msg_categories_cfg * msg_categories_config) {

        amod_classify_obj * obj;

        obj = (amod_classify_obj *) malloc(sizeof(amod_classify_obj));

        obj->mod_classify = mod_classify_construct(mod_classify_config, msg_hops_config, msg_tracks_config, msg_categories_config);
        
        obj->in1 = (amsg_hops_obj *) NULL;
        obj->in2 = (amsg_tracks_obj *) NULL;
        obj->out = (amsg_categories_obj *) NULL;        

        obj->thread = thread_construct(&amod_classify_thread, (void *) obj);

        mod_classify_disable(obj->mod_classify);

        return obj;

    }

    void amod_classify_destroy(amod_classify_obj * obj) {

        mod_classify_destroy(obj->mod_classify);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_classify_connect(amod_classify_obj * obj, amsg_hops_obj * in1, amsg_tracks_obj * in2, amsg_categories_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;        

    }

    void amod_classify_disconnect(amod_classify_obj * obj) {

        obj->in1 = (amsg_hops_obj *) NULL;
        obj->in2 = (amsg_tracks_obj *) NULL;
        obj->out = (amsg_categories_obj *) NULL;

    }

    void amod_classify_enable(amod_classify_obj * obj) {

        mod_classify_enable(obj->mod_classify);

    }

    void amod_classify_disable(amod_classify_obj * obj) {

        mod_classify_disable(obj->mod_classify);

    }

    void * amod_classify_thread(void * ptr) {

        amod_classify_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_tracks_obj * msg_tracks_in;
        msg_categories_obj * msg_categories_out;
        int rtnValue;

        obj = (amod_classify_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in1);
            msg_tracks_in = amsg_tracks_filled_pop(obj->in2);
            msg_categories_out = amsg_categories_empty_pop(obj->out);
            mod_classify_connect(obj->mod_classify, msg_hops_in, msg_tracks_in, msg_categories_out);
            rtnValue = mod_classify_process(obj->mod_classify);
            mod_classify_disconnect(obj->mod_classify);
            amsg_hops_empty_push(obj->in1, msg_hops_in);
            amsg_tracks_empty_push(obj->in2, msg_tracks_in);
            amsg_categories_filled_push(obj->out, msg_categories_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
