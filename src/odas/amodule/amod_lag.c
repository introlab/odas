
    /**
    * \file     amod_lag.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-24
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
    
    #include <amodule/amod_lag.h>

    amod_lag_obj * amod_lag_construct(const mod_lag_cfg * mod_lag_config, const msg_spectra_cfg * msg_spectra_config) {

        amod_lag_obj * obj;

        obj = (amod_lag_obj *) malloc(sizeof(amod_lag_obj));

        obj->mod_lag = mod_lag_construct(mod_lag_config, msg_spectra_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

        obj->thread = thread_construct(&amod_lag_thread, (void *) obj);

        return obj;

    }

    void amod_lag_destroy(amod_lag_obj * obj) {

        mod_lag_destroy(obj->mod_lag);
        thread_destroy(obj->thread);

        free((void *) obj);        

    }

    void amod_lag_connect(amod_lag_obj * obj, amsg_spectra_obj * in, amsg_spectra_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_lag_disconnect(amod_lag_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

    }

    void * amod_lag_thread(void * ptr) {

        amod_lag_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_spectra_obj * msg_spectra_out;
        int rtnValue;

        obj = (amod_lag_obj *) ptr;

        if (obj->in == NULL) {
            printf("amod_lag: nothing connected to input\n");
            exit(EXIT_FAILURE);
        }
        if (obj->out == NULL) {
            printf("amod_lag: nothing connected to output\n");
            exit(EXIT_FAILURE);
        }       

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_spectra_out = amsg_spectra_empty_pop(obj->out);
            mod_lag_connect(obj->mod_lag, msg_spectra_in, msg_spectra_out);
            rtnValue = mod_lag_process(obj->mod_lag);
            mod_lag_disconnect(obj->mod_lag);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_spectra_filled_push(obj->out, msg_spectra_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
