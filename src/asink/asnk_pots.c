
    /**
    * \file     asnk_pots.c
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
    
    #include <asink/asnk_pots.h>

    asnk_pots_obj * asnk_pots_construct(const snk_pots_cfg * snk_pots_config, const msg_pots_cfg * msg_pots_config) {

        asnk_pots_obj * obj;

        obj = (asnk_pots_obj *) malloc(sizeof(asnk_pots_obj));

        obj->snk_pots = snk_pots_construct(snk_pots_config, msg_pots_config);
        obj->in = (amsg_pots_obj *) NULL;

        obj->thread = thread_construct(&asnk_pots_thread, (void *) obj);

        return obj;

    }

    void asnk_pots_destroy(asnk_pots_obj * obj) {

        snk_pots_destroy(obj->snk_pots);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_pots_connect(asnk_pots_obj * obj, amsg_pots_obj * in) {

        obj->in = in;

    }

    void asnk_pots_disconnect(asnk_pots_obj * obj) {

        obj->in = (amsg_pots_obj *) NULL;

    }

    void * asnk_pots_thread(void * ptr) {

        asnk_pots_obj * obj;
        msg_pots_obj * msg_pots_in;
        int rtnValue;

        obj = (asnk_pots_obj *) ptr;

        // Open the sink
        snk_pots_open(obj->snk_pots);

        while(1) {

            // Pop a message, process, and push back
            msg_pots_in = amsg_pots_filled_pop(obj->in);
            snk_pots_connect(obj->snk_pots, msg_pots_in);
            rtnValue = snk_pots_process(obj->snk_pots);
            snk_pots_disconnect(obj->snk_pots);
            amsg_pots_empty_push(obj->in, msg_pots_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_pots_close(obj->snk_pots);

    }
