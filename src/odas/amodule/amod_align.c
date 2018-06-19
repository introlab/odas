    
   /**
    * \file     amod_align.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-24
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

    #include <amodule/amod_align.h>

    amod_align_obj * amod_align_construct(const mod_align_cfg * mod_align_config, const msg_targets_cfg * msg_targets_in_config, const msg_hops_cfg * msg_hops_in_config, const msg_targets_cfg * msg_targets_out_config) {

        amod_align_obj * obj;

        obj = (amod_align_obj *) malloc(sizeof(amod_align_obj));

        obj->mod_align = mod_align_construct(mod_align_config, msg_targets_in_config, msg_hops_in_config, msg_targets_out_config);
        
        obj->in1 = (amsg_targets_obj *) NULL;
        obj->in2 = (amsg_hops_obj *) NULL;
        obj->out = (amsg_targets_obj *) NULL;

        obj->thread = thread_construct(&amod_align_thread, (void *) obj);

        return obj;

    }

    void amod_align_destroy(amod_align_obj * obj) {

        mod_align_destroy(obj->mod_align);
        thread_destroy(obj->thread);

        free((void *) obj);        

    }

    void amod_align_connect(amod_align_obj * obj, amsg_targets_obj * in1, amsg_hops_obj * in2, amsg_targets_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;

    }

    void amod_align_disconnect(amod_align_obj * obj) {

        obj->in1 = (amsg_targets_obj *) NULL;
        obj->in2 = (amsg_hops_obj *) NULL;
        obj->out = (amsg_targets_obj *) NULL;

    }

    void amod_align_enable(amod_align_obj * obj) {

        mod_align_enable(obj->mod_align);

    }

    void amod_align_disable(amod_align_obj * obj) {

        mod_align_disable(obj->mod_align);

    }

    void * amod_align_thread(void * ptr) {

        amod_align_obj * obj;
        msg_targets_obj * msg_targets_in;
        msg_hops_obj * msg_hops_in;
        msg_targets_obj * msg_targets_out;
        
        int rtnValuePush;
        int rtnValuePop;

        obj = (amod_align_obj *) ptr;

        rtnValuePush = 0;
        rtnValuePop = 0;

        while(1) {
                         
            if (rtnValuePush != -1) {
                msg_targets_in = amsg_targets_filled_pop(obj->in1);
            }
            if (rtnValuePop != -1) {
                msg_hops_in = amsg_hops_filled_pop(obj->in2);
                msg_targets_out = amsg_targets_empty_pop(obj->out);
            }

            mod_align_connect(obj->mod_align, msg_targets_in, msg_hops_in, msg_targets_out);
            rtnValuePush = mod_align_process_push(obj->mod_align);
            rtnValuePop = mod_align_process_pop(obj->mod_align);
            mod_align_disconnect(obj->mod_align);

            if (rtnValuePush != -1) {
                amsg_targets_empty_push(obj->in1, msg_targets_in);
            }
            if (rtnValuePop != -1) {
                amsg_hops_empty_push(obj->in2, msg_hops_in);
                amsg_targets_filled_push(obj->out, msg_targets_out);
            }

            // If this is the last frame
            if ((rtnValuePush == -1) && (rtnValuePop == -1)) {
                amsg_targets_empty_push(obj->in1, msg_targets_in);
                amsg_hops_empty_push(obj->in2, msg_hops_in);
                amsg_targets_filled_push(obj->out, msg_targets_out);
                break;
            }

        }        

    }