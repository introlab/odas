
    /**
    * \file     amod_resample.c
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
    
    #include <amodule/amod_resample.h>

    amod_resample_obj * amod_resample_construct(const mod_resample_cfg * mod_resample_config, const msg_hops_cfg * msg_hops_in_config, const msg_hops_cfg * msg_hops_out_config) {

        amod_resample_obj * obj;

        obj = (amod_resample_obj *) malloc(sizeof(amod_resample_obj));

        obj->mod_resample = mod_resample_construct(mod_resample_config, msg_hops_in_config, msg_hops_out_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

        obj->thread = thread_construct(&amod_resample_thread, (void *) obj);

        mod_resample_disable(obj->mod_resample);

        return obj;

    }

    void amod_resample_destroy(amod_resample_obj * obj) {

        mod_resample_destroy(obj->mod_resample);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_resample_connect(amod_resample_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_resample_disconnect(amod_resample_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

    }

    void amod_resample_enable(amod_resample_obj * obj) {

        mod_resample_enable(obj->mod_resample);

    }

    void amod_resample_disable(amod_resample_obj * obj) {

        mod_resample_disable(obj->mod_resample);

    }

    void * amod_resample_thread(void * ptr) {

        amod_resample_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_hops_obj * msg_hops_out;
        int rtnValuePush;
        int rtnValuePop;

        obj = (amod_resample_obj *) ptr;

        rtnValuePush = 0;
        rtnValuePop = 0;

        while(1) {
                         
            if (rtnValuePush != -1) {
                msg_hops_in = amsg_hops_filled_pop(obj->in);
            }
            if (rtnValuePop != -1) {
                msg_hops_out = amsg_hops_empty_pop(obj->out);
            }

            mod_resample_connect(obj->mod_resample, msg_hops_in, msg_hops_out);
            rtnValuePush = mod_resample_process_push(obj->mod_resample);
            rtnValuePop = mod_resample_process_pop(obj->mod_resample);
            mod_resample_disconnect(obj->mod_resample);

            if (rtnValuePush != -1) {
                amsg_hops_empty_push(obj->in, msg_hops_in);
            }
            if (rtnValuePop != -1) {
                amsg_hops_filled_push(obj->out, msg_hops_out);
            }

            // If this is the last frame
            if ((rtnValuePush == -1) && (rtnValuePop == -1)) {
                amsg_hops_empty_push(obj->in, msg_hops_in);
                amsg_hops_filled_push(obj->out, msg_hops_out);
                break;
            }

        }

    }
