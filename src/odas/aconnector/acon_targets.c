
    /**
    * \file     acon_targets.c
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
    
    #include <aconnector/acon_targets.h>

    acon_targets_obj * acon_targets_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_targets_cfg * msg_targets_config) {

        acon_targets_obj * obj;
        unsigned int iOut;

        obj = (acon_targets_obj *) malloc(sizeof(acon_targets_obj));

        obj->in = amsg_targets_construct(nMessages, msg_targets_config);

        obj->outs = (amsg_targets_obj **) malloc(sizeof(amsg_targets_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_targets_construct(nMessages, msg_targets_config);
        }

        obj->con_targets = con_targets_construct(nOuts, msg_targets_config);

        obj->thread = thread_construct(&acon_targets_thread, (void *) obj);

        return obj;

    }

    void acon_targets_destroy(acon_targets_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_targets->nOuts;

        thread_destroy(obj->thread);

        con_targets_destroy(obj->con_targets);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_targets_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_targets_destroy(obj->in);

        free((void *) obj);

    }

    void * acon_targets_thread(void * ptr) {

        msg_targets_obj * msg_targets_in;
        msg_targets_obj * msg_targets_out;

        acon_targets_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_targets_obj *) ptr;

        nOuts = obj->con_targets->nOuts;

        while(1) {

            msg_targets_in = amsg_targets_filled_pop(obj->in);
            msg_targets_copy(obj->con_targets->in, msg_targets_in);
            amsg_targets_empty_push(obj->in, msg_targets_in);

            rtnValue = con_targets_process(obj->con_targets);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_targets_out = amsg_targets_empty_pop(obj->outs[iOut]);
                msg_targets_copy(msg_targets_out, obj->con_targets->outs[iOut]);
                amsg_targets_filled_push(obj->outs[iOut], msg_targets_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
