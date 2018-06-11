
    /**
    * \file     acon_categories.c
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

    #include <aconnector/acon_categories.h>

    acon_categories_obj * acon_categories_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_categories_cfg * msg_categories_config) {

        acon_categories_obj * obj;
        unsigned int iOut;

        obj = (acon_categories_obj *) malloc(sizeof(acon_categories_obj));

        obj->in = amsg_categories_construct(nMessages, msg_categories_config);

        obj->outs = (amsg_categories_obj **) malloc(sizeof(amsg_categories_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_categories_construct(nMessages, msg_categories_config);
        }

        obj->con_categories = con_categories_construct(nOuts, msg_categories_config);

        obj->thread = thread_construct(&acon_categories_thread, (void *) obj);

        return obj;

    }

    void acon_categories_destroy(acon_categories_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_categories->nOuts;

        thread_destroy(obj->thread);

        con_categories_destroy(obj->con_categories);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_categories_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_categories_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_categories_thread(void * ptr) {

        msg_categories_obj * msg_categories_in;
        msg_categories_obj * msg_categories_out;

        acon_categories_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_categories_obj *) ptr;

        nOuts = obj->con_categories->nOuts;

        while(1) {

            msg_categories_in = amsg_categories_filled_pop(obj->in);
            msg_categories_copy(obj->con_categories->in, msg_categories_in);
            amsg_categories_empty_push(obj->in, msg_categories_in);

            rtnValue = con_categories_process(obj->con_categories);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_categories_out = amsg_categories_empty_pop(obj->outs[iOut]);
                msg_categories_copy(msg_categories_out, obj->con_categories->outs[iOut]);
                amsg_categories_filled_push(obj->outs[iOut], msg_categories_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
