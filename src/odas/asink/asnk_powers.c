
    /**
    * \file     asnk_powers.c
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

    #include <asink/asnk_powers.h>

    asnk_powers_obj * asnk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config) {

        asnk_powers_obj * obj;

        obj = (asnk_powers_obj *) malloc(sizeof(asnk_powers_obj));

        obj->snk_powers = snk_powers_construct(snk_powers_config, msg_powers_config);
        obj->in = (amsg_powers_obj *) NULL;

        obj->thread = thread_construct(&asnk_powers_thread, (void *) obj);

        return obj;

    }

    void asnk_powers_destroy(asnk_powers_obj * obj) {

        snk_powers_destroy(obj->snk_powers);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_powers_connect(asnk_powers_obj * obj, amsg_powers_obj * in) {

        obj->in = in;

    }

    void asnk_powers_disconnect(asnk_powers_obj * obj) {

        obj->in = (amsg_powers_obj *) NULL;

    }

    void * asnk_powers_thread(void * ptr) {

        asnk_powers_obj * obj;
        msg_powers_obj * msg_powers_in;
        int rtnValue;

        obj = (asnk_powers_obj *) ptr;

        // Open the sink
        snk_powers_open(obj->snk_powers);

        while(1) {

            // Pop a message, process, and push back
            msg_powers_in = amsg_powers_filled_pop(obj->in);
            snk_powers_connect(obj->snk_powers, msg_powers_in);
            rtnValue = snk_powers_process(obj->snk_powers);
            snk_powers_disconnect(obj->snk_powers);
            amsg_powers_empty_push(obj->in, msg_powers_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_powers_close(obj->snk_powers);

    }
