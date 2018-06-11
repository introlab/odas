
    /**
    * \file     acon_pots.c
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
    
    #include <aconnector/acon_pots.h>

    acon_pots_obj * acon_pots_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_pots_cfg * msg_pots_config) {

        acon_pots_obj * obj;
        unsigned int iOut;

        obj = (acon_pots_obj *) malloc(sizeof(acon_pots_obj));

        obj->in = amsg_pots_construct(nMessages, msg_pots_config);

        obj->outs = (amsg_pots_obj **) malloc(sizeof(amsg_pots_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_pots_construct(nMessages, msg_pots_config);
        }

        obj->con_pots = con_pots_construct(nOuts, msg_pots_config);

        obj->thread = thread_construct(&acon_pots_thread, (void *) obj);

        return obj;

    }

    void acon_pots_destroy(acon_pots_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_pots->nOuts;

        thread_destroy(obj->thread);

        con_pots_destroy(obj->con_pots);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_pots_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_pots_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_pots_thread(void * ptr) {

        msg_pots_obj * msg_pots_in;
        msg_pots_obj * msg_pots_out;

        acon_pots_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_pots_obj *) ptr;

        nOuts = obj->con_pots->nOuts;

        while(1) {

            msg_pots_in = amsg_pots_filled_pop(obj->in);
            msg_pots_copy(obj->con_pots->in, msg_pots_in);
            amsg_pots_empty_push(obj->in, msg_pots_in);

            rtnValue = con_pots_process(obj->con_pots);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_pots_out = amsg_pots_empty_pop(obj->outs[iOut]);
                msg_pots_copy(msg_pots_out, obj->con_pots->outs[iOut]);
                amsg_pots_filled_push(obj->outs[iOut], msg_pots_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
