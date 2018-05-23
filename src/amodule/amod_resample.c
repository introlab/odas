
    /**
    * \file     amod_resample.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
