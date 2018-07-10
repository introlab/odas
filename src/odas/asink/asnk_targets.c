
    /**
    * \file     asnk_targets.c
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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

    #include <asink/asnk_targets.h>

    asnk_targets_obj * asnk_targets_construct(const snk_targets_cfg * snk_targets_config, const msg_targets_cfg * msg_targets_config) {

        asnk_targets_obj * obj;

        obj = (asnk_targets_obj *) malloc(sizeof(asnk_targets_obj));

        obj->snk_targets = snk_targets_construct(snk_targets_config, msg_targets_config);
        obj->in = (amsg_targets_obj *) NULL;

        obj->thread = thread_construct(&asnk_targets_thread, (void *) obj);

        return obj;

    }

    void asnk_targets_destroy(asnk_targets_obj * obj) {

        snk_targets_destroy(obj->snk_targets);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_targets_connect(asnk_targets_obj * obj, amsg_targets_obj * in) {

        obj->in = in;

    }

    void asnk_targets_disconnect(asnk_targets_obj * obj) {

        obj->in = (amsg_targets_obj *) NULL;

    }

    void * asnk_targets_thread(void * ptr) {

        asnk_targets_obj * obj;
        msg_targets_obj * msg_targets_in;
        int rtnValue;

        obj = (asnk_targets_obj *) ptr;

        if (obj->in == NULL) {
            printf("asnk_tracks: nothing connected to input\n");
            exit(EXIT_FAILURE);
        }

        // Open the sink
        snk_targets_open(obj->snk_targets);

        while(1) {

            // Pop a message, process, and push back
            msg_targets_in = amsg_targets_filled_pop(obj->in);
            snk_targets_connect(obj->snk_targets, msg_targets_in);
            rtnValue = snk_targets_process(obj->snk_targets);
            snk_targets_disconnect(obj->snk_targets);
            amsg_targets_empty_push(obj->in, msg_targets_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_targets_close(obj->snk_targets);

    }
