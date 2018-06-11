
    /**
    * \file     amod_volume.c
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
    
    #include <amodule/amod_volume.h>

    amod_volume_obj * amod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config) {

        amod_volume_obj * obj;

        obj = (amod_volume_obj *) malloc(sizeof(amod_volume_obj));

        obj->mod_volume = mod_volume_construct(mod_volume_config, msg_hops_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

        obj->thread = thread_construct(&amod_volume_thread, (void *) obj);

        mod_volume_disable(obj->mod_volume);

        return obj;        

    }

    void amod_volume_destroy(amod_volume_obj * obj) {

        mod_volume_destroy(obj->mod_volume);
        thread_destroy(obj->thread);

        free((void *) obj);  

    }

    void amod_volume_connect(amod_volume_obj * obj, amsg_hops_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_volume_disconnect(amod_volume_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

    }

    void amod_volume_enable(amod_volume_obj * obj) {

        mod_volume_enable(obj->mod_volume);

    }

    void amod_volume_disable(amod_volume_obj * obj) {

        mod_volume_disable(obj->mod_volume);

    }

    void * amod_volume_thread(void * ptr) {

        amod_volume_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (amod_volume_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_hops_out = amsg_hops_empty_pop(obj->out);
            mod_volume_connect(obj->mod_volume, msg_hops_in, msg_hops_out);
            rtnValue = mod_volume_process(obj->mod_volume);
            mod_volume_disconnect(obj->mod_volume);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_hops_filled_push(obj->out, msg_hops_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
