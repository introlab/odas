
    /**
    * \file     amod_sst.c
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

    #include <amodule/amod_sst.h>

    amod_sst_obj * amod_sst_construct(const mod_sst_cfg * mod_sst_config, const mod_ssl_cfg * mod_ssl_config, const msg_pots_cfg * msg_pots_config, const msg_targets_cfg * msg_targets_config, const msg_tracks_cfg * msg_tracks_config) {

        amod_sst_obj * obj;

        obj = (amod_sst_obj *) malloc(sizeof(amod_sst_obj));

        obj->mod_sst = mod_sst_construct(mod_sst_config, mod_ssl_config, msg_pots_config, msg_targets_config, msg_tracks_config);
        
        obj->in1 = (amsg_pots_obj *) NULL;
        obj->in2 = (amsg_targets_obj *) NULL;
        obj->out = (amsg_tracks_obj *) NULL;

        obj->thread = thread_construct(&amod_sst_thread, (void *) obj);

        mod_sst_disable(obj->mod_sst);

        return obj;

    }

    void amod_sst_destroy(amod_sst_obj * obj) {

        mod_sst_destroy(obj->mod_sst);
        thread_destroy(obj->thread);

        free((void *) obj); 

    }

    void amod_sst_connect(amod_sst_obj * obj, amsg_pots_obj * in1, amsg_targets_obj * in2, amsg_tracks_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;

    }

    void amod_sst_disconnect(amod_sst_obj * obj) {

        obj->in1 = (amsg_pots_obj *) NULL;
        obj->in2 = (amsg_targets_obj *) NULL;
        obj->out = (amsg_tracks_obj *) NULL;

    }

    void amod_sst_enable(amod_sst_obj * obj) {

        mod_sst_enable(obj->mod_sst);

    }

    void amod_sst_disable(amod_sst_obj * obj) {

        mod_sst_disable(obj->mod_sst);

    }

    void * amod_sst_thread(void * ptr) {

        amod_sst_obj * obj;
        msg_pots_obj * msg_pots_in;
        msg_targets_obj * msg_targets_in;
        msg_tracks_obj * msg_tracks_out;
        int rtnValue;

        obj = (amod_sst_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_pots_in = amsg_pots_filled_pop(obj->in1);
            msg_targets_in = amsg_targets_filled_pop(obj->in2);
            msg_tracks_out = amsg_tracks_empty_pop(obj->out);
            mod_sst_connect(obj->mod_sst, msg_pots_in, msg_targets_in, msg_tracks_out);
            rtnValue = mod_sst_process(obj->mod_sst);
            mod_sst_disconnect(obj->mod_sst);
            amsg_pots_empty_push(obj->in1, msg_pots_in);
            amsg_targets_empty_push(obj->in2, msg_targets_in);
            amsg_tracks_filled_push(obj->out, msg_tracks_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
