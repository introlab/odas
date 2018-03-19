
    /**
    * \file     acon_spectra.c
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
    
    #include <aconnector/acon_spectra.h>

    acon_spectra_obj * acon_spectra_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_spectra_cfg * msg_spectra_config) {

        acon_spectra_obj * obj;
        unsigned int iOut;

        obj = (acon_spectra_obj *) malloc(sizeof(acon_spectra_obj));

        obj->in = amsg_spectra_construct(nMessages, msg_spectra_config);

        obj->outs = (amsg_spectra_obj **) malloc(sizeof(amsg_spectra_obj *) * nOuts);
        for (iOut = 0; iOut < nOuts; iOut++) {
            obj->outs[iOut] = amsg_spectra_construct(nMessages, msg_spectra_config);
        }

        obj->con_spectra = con_spectra_construct(nOuts, msg_spectra_config);

        obj->thread = thread_construct(&acon_spectra_thread, (void *) obj);

        return obj;

    }

    void acon_spectra_destroy(acon_spectra_obj * obj) {

        unsigned int iOut;
        unsigned int nOuts;

        nOuts = obj->con_spectra->nOuts;

        thread_destroy(obj->thread);

        con_spectra_destroy(obj->con_spectra);

        for (iOut = 0; iOut < nOuts; iOut++) {
            amsg_spectra_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        amsg_spectra_destroy(obj->in);

        free((void *) obj);


    }

    void * acon_spectra_thread(void * ptr) {

        msg_spectra_obj * msg_spectra_in;
        msg_spectra_obj * msg_spectra_out;

        acon_spectra_obj * obj;
        unsigned int iOut;
        unsigned int nOuts;
        int rtnValue;

        obj = (acon_spectra_obj *) ptr;

        nOuts = obj->con_spectra->nOuts;

        while(1) {

            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_spectra_copy(obj->con_spectra->in, msg_spectra_in);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);

            rtnValue = con_spectra_process(obj->con_spectra);

            for (iOut = 0; iOut < nOuts; iOut++) {
                
                msg_spectra_out = amsg_spectra_empty_pop(obj->outs[iOut]);
                msg_spectra_copy(msg_spectra_out, obj->con_spectra->outs[iOut]);
                amsg_spectra_filled_push(obj->outs[iOut], msg_spectra_out);

            }

            if (rtnValue == -1) {
                break;
            }

        }

    }
