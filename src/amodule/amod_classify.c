
    /**
    * \file     amod_classify.c
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
    
    #include <amodule/amod_classify.h>

    amod_classify_obj * amod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config, const msg_categories_cfg * msg_categories_config) {

        amod_classify_obj * obj;

        obj = (amod_classify_obj *) malloc(sizeof(amod_classify_obj));

        obj->mod_classify = mod_classify_construct(mod_classify_config, msg_hops_config, msg_tracks_config, msg_categories_config);
        
        obj->in1 = (amsg_hops_obj *) NULL;
        obj->in2 = (amsg_tracks_obj *) NULL;
        obj->out = (amsg_categories_obj *) NULL;        

        obj->thread = thread_construct(&amod_classify_thread, (void *) obj);

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
