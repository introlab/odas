
    /**
    * \file     asnk_hops.c
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
    
    #include <asink/asnk_hops.h>

    asnk_hops_obj * asnk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config) {

        asnk_hops_obj * obj;

        obj = (asnk_hops_obj *) malloc(sizeof(asnk_hops_obj));

        obj->snk_hops = snk_hops_construct(snk_hops_config, msg_hops_config);
        obj->in = (amsg_hops_obj *) NULL;

        obj->thread = thread_construct(&asnk_hops_thread, (void *) obj);

        return obj;

    }

    void asnk_hops_destroy(asnk_hops_obj * obj) {

        snk_hops_destroy(obj->snk_hops);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_hops_connect(asnk_hops_obj * obj, amsg_hops_obj * in) {

        obj->in = in;

    }

    void asnk_hops_disconnect(asnk_hops_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;

    }

    void * asnk_hops_thread(void * ptr) {

        asnk_hops_obj * obj;
        msg_hops_obj * msg_hops_in;
        int rtnValue;

        obj = (asnk_hops_obj *) ptr;

        // Open the sink
        snk_hops_open(obj->snk_hops);

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            snk_hops_connect(obj->snk_hops, msg_hops_in);
            rtnValue = snk_hops_process(obj->snk_hops);
            snk_hops_disconnect(obj->snk_hops);
            amsg_hops_empty_push(obj->in, msg_hops_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_hops_close(obj->snk_hops);

    }
