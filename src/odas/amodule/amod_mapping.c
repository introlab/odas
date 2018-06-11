
    /**
    * \file     amod_mapping.c
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
